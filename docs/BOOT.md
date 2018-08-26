# Notes about the boot process

## Bootloader

The bootloader uses a heavily modified
[LK (Little Kernel)](https://github.com/littlekernel/lk/wiki/Introduction).

## Boot modes

The bootloader sets the boot mode, and depending on it may or may not
initialize the baseband etc.

The Android kernel also initializes hardware in wildly different ways based
on the boot mode - e.g. battery may constantly report being at 75%, battery
temperature check may be ignored, USB and HDMI may be initialized differently
etc.

The boot mode is communicated to the kernel in the device tree, in
`/chosen/atag,boot`.

| Boot                                          | Boot mode      | Partition  | Effect                                           |
| --------------------------------------------- | -------------- | ---------- | ------------------------------------------------ |
| Boot 1 (nothing pressed)                      | `NORMAL_BOOT`  | `boot`     | Android kernel does not initialize the USB UART. |
| Recovery (ESC held during boot)               | ?              | `recovery` | The baseband is not initialized.                 |
| Boot 2 (side button held during boot)         | `FACTORY_BOOT` | `boot2`    |                                                  |
| Boot 3 (ESC and side button held during boot) | ?              | `boot3`    |                                                  |

## Boot images

- The boot images are Android boot images
- The images have the compiled device tree (DTB) concatenated after the linux
  image. Note that `binwalk` does not see this, but it can be extracted
  manually:  
  ```bash
  binwalk -e --carve image.img
  # In extracted directory, on 800.gz or Image.gz or whatever
  grep -Fb --only-matching --text `echo -e "\xd0\x0d\xfe\xed"` 800.gz
  # Prints: 8344557:
  # NOTE: the number in tail is incremented by one.
  tail -c +8344558 800.gz >boot.dtb
  dtc -I dtb dtb
  ```
- Memory location of `initrd` is passed to the kernel in `linux,initrd-start`
  and `linux,initrd-end` in the device tree.

## Boot loader failure

If MediaTek's LK fails at boot, the output will be like 

```
[2231] [ccci] modem mem info not support
[ATF](0)[10.075528]aee_wdt_dump: on cpu0
[ATF](0)[10.075954](0) pc:<000000004602984c> lr:<0000000000000000> sp:<0000000000000000> pstate: 60000173
[ATF](0)[10.077105](0) x29: 0000000046071400 x28: 0000000000000000 x27: 0000000000000000
[ATF](0)[10.078075](0) x26: 0000000000000000 x25: 0000000000000000 x24: 0000000000000000
[ATF](0)[10.079044](0) x23: 0000000046071400 x22: 0000000000000000 x21: 0000000046071400
[ATF](0)[10.080013](0) x20: 0000000000000000 x19: 000000004608c778 x18: 000000004602fc35
[ATF](0)[10.080983](0) x17: 0000000046073cac x16: 0000000046029850 x15: 0000000000000000
[ATF](0)[10.081951](0) x14: 0000000000000000 x13: 0000000000000000 x12: 0000000040000000
[ATF](0)[10.082921](0) x11: 0000000000000010 x10: 000000004605cf9c x09: 000000000c54fd96
[ATF](0)[10.083890](0) x08: 0000000000000000 x07: 0000000040080000 x06: 0000000046071528
[ATF](0)[10.084859](0) x05: 0000000044000000 x04: 00000000002ef315 x03: 000000000000036e
[ATF](0)[10.085828](0) x02: 00000000fffffffd x01: 000000000000298c x00: 0000000000000000
[ATF](0)[10.086799]inter-cpu-call interrupt is triggered
[ATF](0)[10.087422]cfd[0] is invalid (func = 0x0, lock = 0)
[ATF](0)[10.088079]CPU_0 cfd lock = 0
[10040] lk_wdt_dump(): watchdog timeout in LK....
[10040] current_thread = bootstrap2
[10041] Dump register from ATF..
[10041] CPSR: 0x60000173
[10041] PC: 0x4602984c
[10042] SP: 0x4608c778
[10042] LR: 0x4602fc35
```

The PC location `0x4602984c` means that the boot process has failed in *some*
way and the bootloader has jumped into a busyloop.

Likely, something is off with the device tree. See **Things to note about the
bootloader**.

## Things to note about the bootloader

### `bootopt=64S3,32N2,64N2` parsing

64 has to appear after the 18th character in the cmdline. `bootopt=` and the
other values are irrelevant.

### DTB size

The bootloader writes new properties in the device tree. It uses the free space
at the end of the device tree for these. If the device tree runs out of space,
boot will fail.

Device tree should be resized before concatenating to accommodate the extra
properties:

```
dtc --in-format dtb --out-format dtb --pad 16384 --out gemini.dtb.fixed gemini.dtb
mv gemini.dtb.fixed gemini.dtb
cat Image.gz gemini.dtb > Image-With-DTB
```

### CPU `clock-frequency` entries

The bootloader expects `clock-frequency` properties to be present on all CPU
nodes. If they are not, it might fail in mysterious ways.

## Device tree: `firmware` node

The bootloader adds a `firmware` node with Compatible: `android,firmware` in the
device tree.

The node contains modem-related settings and the serial number of the device.
All of the options below are under `firmware/android`.

| Option              | Description                                                                                                               |
| ------------------- | ------------------------------------------------------------------------------------------------------------------------- |
| `opt_c2k_lte_mode`  | Referred to by `ccci_util`.                                                                                               |
| `opt_c2k_support`   | Referred to by `ccci_util`.                                                                                               |
| `opt_eccci_c2k`     | Referred to by `ccci_util`.                                                                                               |
| `opt_irat_support`  | Referred to by `ccci_util`.                                                                                               |
| `opt_lte_support`   | No references in the Android kernel.                                                                                      |
| `opt_md1_support`   | Referred to by `ccci_util`.                                                                                               |
| `opt_md3_support`   | Referred to by `ccci_util`.                                                                                               |
| `opt_ps1_rat`       | No references in the Android kernel.                                                                                      |
| `opt_using_default` | No references in the Android kernel. The using default value is parsed as the non-existence of `opt_using_lk_val` option. |
| `serialno`          | Contains the serial number of the device.                                                                                 |

Additionally, `ccci_util` refers to properties not in the device tree:

- `opt_md2_support`
- `opt_md5_support`
- Possibly other `opt_md*_support` values, since there is a loop that checks them.

## Device tree: `memory/orig_dram_info` property

Structure:

| Field           | Offset | Bytes       |
| --------------- | -----  | ----------- |
| Rank number     | 0x00   | 4           |
| Start address 0 | 0x04   | 8           |
| Size 0          | 0x0C   | 8           |
| Start address 1 | 0x14   | 8           |
| Size 1          | 0x1C   | 8           |
| Start address 2 | 0x24   | 8           |
| Size 2          | 0x2C   | 8           |
| Start address 3 | 0x34   | 8           |
| Size 3          | 0x3C   | 8           |

## Device tree: `chosen/ccci,modem_info_v2` property

The boot loader adds a `ccci,modem_info_v2` into `chosen`. This is read by
`ccci_util`.

The tag is stored in little-endian format, not in big-endian as normal device
tree properties.

| Field        | Offset |       Bytes | Description                    |
| ------------ | ------ | ----------- | -----------                    |
| Base address |   0x00 |           8 | Base address of the modem.     |
| Size         |   0x08 |           4 | Size of the modem memory area. |
| Error number |   0x0C |           4 |                                |
| Version      |   0x10 |           4 |                                |
| Tag number   |   0x14 |           4 |                                |
| LD flag      |   0x18 |           4 |                                |
| LD error 0   |   0x1C |           4 |                                |
| LD error 1   |   0x20 |           4 |                                |
| LD error 2   |   0x24 |           4 |                                |
| LD error 3   |   0x28 |           4 |                                |

## Device tree: ATAGs

The device tree contains various `atag,` values in `chosen/`. The values are
not interpreted by the mainline kernel, as ATAGs are a 32-bit ARM thing.

| ATAG                    | Description                                                                    |
| ----------------------- | ------------------------------------------------------------------------------ |
| `boot`                  | Boot mode of the device.                                                       |
| `boot_voltage`          | **TODO**                                                                       |
| `cmdline`               | The boot commandline of the kernel.                                            |
| `devinfo`               | **TODO**                                                                       |
| `extbuck_fan53526`      | **TODO**                                                                       |
| `fg_swocv_i`            | Uninitialized data.                                                            |
| `fg_swocv_v`            | Uninitialized data.                                                            |
| `imix_r`                | **TODO**                                                                       |
| `masp`                  | **TODO**                                                                       |
| `mdinfo`                | Referred to by `ccci_util`. See also `chosen/ccci,modem_info_v2`.              |
| `mem`                   | **TODO**                                                                       |
| `ptp`                   | **TODO**                                                                       |
| `shutdown_time`         | **TODO**                                                                       |
| `videolfb`              | **TODO**                                                                       |
| `videolfb-fb_base_h`    | Framebuffer address, high `u32`. This is zero.                                 |
| `videolfb-fb_base_i`    | Framebuffer address, low `u32`.                                                |
| `videolfb-islcmfound`   | **TODO**                                                                       |
| `videolfb-islcm_inited` | **TODO**                                                                       |
| `videolfb-fps`          | Measured framerate of the display. Changes by a few FPS between boots.         |
| `videolfb-vramSize`     | Size of the framebuffer, in bytes.                                             |

## Boot CMDLINEs

Boot lines for the kernel are similar between Linux and Android, only differing
in `buildvariant=user`. `androidboot.serialno` is sanitized in the examples
below.

The boot CMDLINE in the boot image has `bootopt=64S3,32N2,64N2` in it.
The Android kernel contains no reference to it, so it is presumably read by
the MediaTek boot loader. Images for other MediaTek devices also contain the
same line.

### Android:

```
console=tty0
console=ttyMT0,921600n1
root=/dev/ram
vmalloc=496M
slub_max_order=0
slub_debug=OFZPU
androidboot.hardware=mt6797
maxcpus=5
androidboot.verifiedbootstate=green
bootopt=64S3,32N2,64N2
buildvariant=user
printk.disable_uart=1
bootprof.pl_t=1490
bootprof.lk_t=2857
boot_reason=4
androidboot.serialno=XXXXXXXXXXXXXXXX
androidboot.bootreason=wdt_by_pass_pwk
gpt=1
usb2jtag_mode=0
```

### Gemian:

```
console=tty0
console=ttyMT0,921600n1
root=/dev/ram
vmalloc=496M
slub_max_order=0
slub_debug=OFZPU
androidboot.hardware=mt6797
maxcpus=5
androidboot.verifiedbootstate=green
bootopt=64S3,32N2,64N2
printk.disable_uart=1
bootprof.pl_t=1490
bootprof.lk_t=2895
boot_reason=4
androidboot.serialno=XXXXXXXXXXXXXXXX
androidboot.bootreason=wdt_by_pass_pwk
gpt=1
usb2jtag_mode=0
```
