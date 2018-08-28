# Mainline Linux kernel on the Gemini PDA :penguin:

This is my attempt to compile a mainline kernel for the Gemini PDA.

:warning: For regular users, this kernel does nothing useful (display, keyboard,
etc. don't work). Don't use it unless you are interested in kernel development
**and willing to risk frying your Gemini.** :warning:

## What works

Currently, only serial console works. The system boots into BusyBox, which is
accessible over the serial console 
([with the USB FTDI cable](http://www.omegamoon.com/blog/index.php?entry=entry180626-210224)).

## Docs and notes about the Gemini PDA

[See the docs directory.](docs/README.md)

## Compiling

:warning: Building with buildroot requires around 10 gigabytes of disk space.

1. Clone this repository.
2. Run `make init`, to build mkbootimg and to initialize buildroot to defconfig.
3. Run `make toolchain` to build the cross-compilation toolchain. This will take
   a while.
4. Run `make` to build the image. This will also take a while. The image will
   appear in `output/boot_linux.img`.
5. `dd` the image to the recovery partition, connect your UART cable, boot and
   enjoy the mainline kernel!

### Build cache

The `defconfig` for buildroot uses build cache. The cache is in
`~/.buildroot-ccache`. Buildroot does not clear it, you must manually empty
the directory to clear the build cache.

### Custom after-build script.

You can add a custom script to run after the build in 
`scripts/custom-after-build.sh`. It will be executed after a successful build
(full-image builds only, i.e. `make`, not `make rebuild-linux`). The script
runs in the root of the repository. You can e.g. copy the image to a server
for easy flashing.

## Changing things

### Linux kernel

When making any changes to the kernel configuration, sources, or the device
tree, the kernel has to be rebuilt separately: 

```bash
make linux-rebuild all
```

`all` is the default make target, so the above command will first rebuild the
kernel, followed by rest of the build operations.

#### Device tree

The device tree is located at `board/gemini-pda/gemini-pda.dts`.

#### Menuconfig

```bash
make linux-menuconfig
```

**NOTE:** the resulting `.config` will be saved in
`ext/buildroot/output/build/linux-*/.config`, and you will need to copy
it to `board/gemini-pda/kernel.config` to yourself to preserve your changes.

#### Linux kernel source

You can edit the Linux source in `ext/buildroot/output/build/linux-*`.
Note that the changes will be lost if the kernel is cleaned with
`make linux-dirclean`, so make sure to export the modifications as patches.

### Buildroot menuconfig

```bash
make menuconfig 
```

**NOTE:** the Buildroot `.config` file will be saved in `ext/buildroot/.config`,
and you will need to copy it to `configs/defconfig` yourself to preserve your
changes.

## Running the kernel without flashing

You can `kexec` into the new kernel dynamically. To facilitate this, there are
two scripts: `kexecboot.sh` and `run-kexecboot.sh`. `kexecboot.sh` runs on the
device, and `run-kexecboot.sh` runs on the host. `run-kexecboot.sh ttyUSB0`
opens `ttyUSB0`, writes to the terminal `/usr/local/bin/kexecboot.sh`, and then
transfers the latest build results to the PDA. The PDA then patches the device
tree and `kexec`s into the new kernel. Note that the transfer takes about a
minute, so it's not significantly faster than booting to Gemian and `dd`ing the
image to recovery.

You can make `scripts/custom-after-build.sh` run `run-kexecboot.sh` after every
build.

## Directory structure

| Directory                       | Description                                                    |
| ------------------------------- | -------------------------------------------------------------- |
| `board/gemini-pda`              | Contains the DTS and kernel, uClibc-ng, and busybox configs.   |
| `board/gemini-pda/root-overlay` | Contains the files copied over the root filesystem.            |
| `configs`                       | Contains Buildroot's defconfig                                 |
| `docs`                          | Notes about the Gemini PDA hardware and configuration.         |
| `ext`                           | External dependencies, as                                      |
| `logs`                          | Contains log files from terminal runs.                         |
| `output`                        | Will contain the built boot image.                             |
| `package`                       | Custom Buildroot packages. Contains the `mt6797_debug module.` |
| `scripts`                       | `run-minicom.sh` and build-related scripts.                    |

## Terminal utility

Running `./scripts/run-minicom.sh ttyUSB0` will open a `minicom` terminal with
the correct settings for Gemini. It will also store logs into the `logs/`
directory.

## `mt6797_debug` module

The included `mt6797_debug` module provides MT6797-specific files in
`/sys/kernel/debug/mt6797`. The module is loaded by default.

### Debugfs files

| File                        | Description                                                                                                               |
| --------------------------- | ------------------------------------------------------------------------------------------------------------------------- |
| `emi_mpu`                   | Information about memory regions protected with EMI MPU                                                                   |
| `pll_bus`                   | Measured frequency of the main AXI bus clock. :warning: **Reading this file has a race condition with the clock driver.** |
| `psci_status`               | PSCI-reported status of CPUs                                                                                              |
| `regs/EMI_CONM`             | Contents of the EMI_CONM register (memory clocks)                                                                         |
| `regs/M4U_PT_BASE_ADDR`     | Base address of M4U page table                                                                                            |
| `regs/M4U_PT_BASE_ADDR_SEC` | Second base address of M4U page table                                                                                     |
| `regs/M4U_CTRL`             | Control registers of M4U                                                                                                  |
| `regs/M4U_IVRP_PADDR`       | Address of M4U's violation info area                                                                                      |
| `regs/*`                    | Various other registers                                                                                                   |

### Rebuilding the module

The module can be rebuilt with `make mt6797_debug-rebuild all`.

## Kernel patch sets

The following patch sets are included:

### Fix `clk`

This patchset marks critical clocks as such. Without these patches, the memory
would get corrupted.

[The patch set has been sent to MediaTek's Linux mailing list.](http://lists.infradead.org/pipermail/linux-mediatek/2018-August/014824.html)

### Fix `scpsys`

This patchset adds missing power domains to scpsys, otherwise the probe for
`scpsys` would fail.
