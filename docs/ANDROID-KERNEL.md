# Notes about MT6797 support in the original Android kernel

Most MediaTek-specific drivers are located in `drivers/misc/mediatek`.

## Modules

Only the top-level directories under `drivers/misc/mediatek` are listed below.

| Module                      | Used?                         | Description                                                                                                                             |
| --------------------------- | ----------------------------- | --------------------------------------------------------------------------------------------------------------------------------------- |
| `accdet`                    | :ballot_box_with_check:       | Accessory detector. Detects if headphones are connected.                                                                                |
| `accelerometer`             | :ballot_box_with_check:       |                                                                                                                                         |
| `activity_sensor`           | :negative_squared_cross_mark: |                                                                                                                                         |
| `aee`                       | :ballot_box_with_check:       | Android Exception Engine. Provides kernel crash dumps.                                                                                  |
| `almk`                      | :negative_squared_cross_mark: | Not included fromthe main Makefile. Possibly related to JPEG encoding.                                                                  |
| `alsps`                     | :ballot_box_with_check:       | Ambient light sensor.                                                                                                                   |
| `answer_call_sensor`        | :negative_squared_cross_mark: |                                                                                                                                         |
| `atf_log`                   | :ballot_box_with_check:       | Reads firmware log from ARM Trusted Firmware, exposes it in `/proc/atf_log`                                                             |
| `audio_ipi`                 | :negative_squared_cross_mark: |                                                                                                                                         |
| `auxadc`                    | :ballot_box_with_check:       | Generic 16-channel ADC for measuring e.g. temperatures.                                                                                 |
| `aw9120`                    | :ballot_box_with_check:       | The LED controller.                                                                                                                     |
| `aw9523`                    | :ballot_box_with_check:       | The keyboard controller.                                                                                                                |
| `barometer`                 | :negative_squared_cross_mark: |                                                                                                                                         |
| `base`                      | :negative_squared_cross_mark: | Power-related stuff. This is used as include path, but not built as a module.                                                           |
| `boot`                      | :ballot_box_with_check:       | Boot mode querying + querying the UART handed by the bootloader.                                                                        |
| `boot_reason`               | :ballot_box_with_check:       | Support for reading the boot reason (not boot mode)                                                                                     |
| `btcvsd`                    | :negative_squared_cross_mark: | The same support is added from a different driver in `sound/soc/mediatec/mt_soc_audio_6797`.                                            |
| `btif`                      | :ballot_box_with_check:       | Bluetooth interface                                                                                                                     |
| `c2k_ccci`                  | :ballot_box_with_check:       | Related to modem (c2k probably stands for CDMA2000)                                                                                     |
| `c2k_usb`                   | :ballot_box_with_check:       | Related to modem (c2k probably stands for CDMA2000)                                                                                     |
| `cam_cal`                   | :ballot_box_with_check:       |                                                                                                                                         |
| `cameraisp`                 | :ballot_box_with_check:       |                                                                                                                                         |
| `ccci_util`                 | :ballot_box_with_check:       | Common functionality for communicating with the baseband (CCCI = Cross-Core Communication Interface)                                    |
| `ccmni`                     | :negative_squared_cross_mark: |                                                                                                                                         |
| `chargepump`                | :negative_squared_cross_mark: |                                                                                                                                         |
| `chip`                      | :ballot_box_with_check:       | Provides version etc. about the chip (SOC).                                                                                             |
| `cmdq`                      | :ballot_box_with_check:       |                                                                                                                                         |
| `conn_md`                   | :ballot_box_with_check:       |                                                                                                                                         |
| `connectivity`              | :ballot_box_with_check:       | An absolutely huge mega-driver containing code for the baseband (including WIFI and Bluetooth)                                          |
| `cqdma`                     | :negative_squared_cross_mark: |                                                                                                                                         |
| `crypto`                    | :negative_squared_cross_mark: | Test module for crypto. Not included in the main Makefile.                                                                              |
| `debug_latch`               | :ballot_box_with_check:       | Debugging facility saving the last program counter and bus access on a crash.                                                           |
| `debug_tracer`              | :negative_squared_cross_mark: | Bus access debugging facility.                                                                                                          |
| `devapc`                    | :ballot_box_with_check:       | Handles access violations on the EMI (External Memory Interface), maybe something else too?                                             |
| `devinfo`                   | :ballot_box_with_check:       | Exports device information on `sysfs` or `debugfs`, depending on configuration. On the Gemini, this is exported to /sys/devices/devmap. |
| `dramc`                     | :ballot_box_with_check:       | DRAM controller (DRAM refresh parameters, etc.)                                                                                         |
| `dual_ccci`                 | :negative_squared_cross_mark: | Support for dual modems.                                                                                                                |
| `dum-char`                  | :negative_squared_cross_mark: |                                                                                                                                         |
| `dws`                       | :black_square_button:         | XML configuration for MediaTek's configurator tool (DCT). Not used by the kernel.                                                       |
| `dynamic_boost`             | :negative_squared_cross_mark: | CPU boost                                                                                                                               |
| `eccci`                     | :ballot_box_with_check:       | Evolved Cross-Core Communication Interface. An updated version of the baseband communication interface. Used on the MT6797.             |
| `emi_bwl`                   | :ballot_box_with_check:       | Bandwidth limiter for the EMI (External memory interface).                                                                              |
| `emi_mbw`                   | :ballot_box_with_check:       | Perhaps a bandwidth monitor for the EMI (External memory interface)?                                                                    |
| `emi_mpu`                   | :ballot_box_with_check:       | Common code for the EMI (External memory interface)                                                                                     |
| `exm`                       | :negative_squared_cross_mark: | External memory. Some MediaTek-internal thing, not included in the main Makefile.                                                       |
| `ext_disp`                  | :negative_squared_cross_mark: |                                                                                                                                         |
| `ext_gic`                   | :negative_squared_cross_mark: | Related to the GIC (global interrupt controller)                                                                                        |
| `face_down_sensor`          | :negative_squared_cross_mark: |                                                                                                                                         |
| `flashlight`                | :ballot_box_with_check:       | The driver is set to a dummy driver.                                                                                                    |
| `freefall_sensor`           | :negative_squared_cross_mark: |                                                                                                                                         |
| `freqhopping`               | :ballot_box_with_check:       | Related to PLLs.                                                                                                                        |
| `gamerotationvector`        | :negative_squared_cross_mark: |                                                                                                                                         |
| `gcpu`                      | :negative_squared_cross_mark: | Trustonic Trusted Execution Environment driver.                                                                                         |
| `geomagneticrotationvector` | :negative_squared_cross_mark: |                                                                                                                                         |
| `gesture`                   | :negative_squared_cross_mark: |                                                                                                                                         |
| `glance_gesture_sensor`     | :negative_squared_cross_mark: |                                                                                                                                         |
| `gpio`                      | :ballot_box_with_check:       | Contains Gemini-specific GPIO code.                                                                                                     |
| `gpt`                       | :negative_squared_cross_mark: | General-purpose timer.                                                                                                                  |
| `gpu`                       | :ballot_box_with_check:       | Mali support                                                                                                                            |
| `gravity`                   | :negative_squared_cross_mark: |                                                                                                                                         |
| `gud`                       | :negative_squared_cross_mark: | Trustonic trusted execution environemnt-related.                                                                                        |
| `gyroscope`                 | :ballot_box_with_check:       |                                                                                                                                         |
| `hdmi`                      | :ballot_box_with_check:       |                                                                                                                                         |
| `heart_rate_sensor`         | :negative_squared_cross_mark: |                                                                                                                                         |
| `humidity`                  | :negative_squared_cross_mark: |                                                                                                                                         |
| `hwmon`                     | :ballot_box_with_check:       |                                                                                                                                         |
| `i2c`                       | :ballot_box_with_check:       |                                                                                                                                         |
| `ice_debug`                 | :negative_squared_cross_mark: | In-circuit emulator? Only used on MT8137.                                                                                               |
| `imgsensor`                 | :ballot_box_with_check:       |                                                                                                                                         |
| `ir_learning`               | :negative_squared_cross_mark: |                                                                                                                                         |
| `irq`                       | :negative_squared_cross_mark: |                                                                                                                                         |
| `irtx`                      | :ballot_box_with_check:       | IR (infrared) transmitter                                                                                                               |
| `jpeg`                      | :ballot_box_with_check:       | Hardware JPEG encoder/decoder                                                                                                           |
| `lcm`                       | :ballot_box_with_check:       | The display module drivers. LCM stands for LCD module.                                                                                  |
| `leds`                      | :ballot_box_with_check:       |                                                                                                                                         |
| `lens`                      | :ballot_box_with_check:       | Autofocus lens driver.                                                                                                                  |
| `linearacceleration`        | :negative_squared_cross_mark: |                                                                                                                                         |
| `log_store`                 | :ballot_box_with_check:       | Reads bootloader logs from DRAM.                                                                                                        |
| `m4u`                       | :ballot_box_with_check:       | Multimedia memory related thing.                                                                                                        |
| `mach`                      | :ballot_box_with_check:       | Only config options, no code.                                                                                                           |
| `magnetometer`              | :negative_squared_cross_mark: |                                                                                                                                         |
| `masp`                      | :ballot_box_with_check:       | Security functions.                                                                                                                     |
| `md32`                      | :negative_squared_cross_mark: |                                                                                                                                         |
| `mem`                       | :ballot_box_with_check:       | Memory information for other drivers and debug.                                                                                         |
| `memory-lowpower`           | :negative_squared_cross_mark: |                                                                                                                                         |
| `memory-ssvp`               | :negative_squared_cross_mark: |                                                                                                                                         |
| `mjc`                       | :ballot_box_with_check:       | Enhanced multimedia playback, related to m4u.                                                                                           |
| `mlog`                      | :ballot_box_with_check:       | Logs memory information in RAM.                                                                                                         |
| `mmp`                       | :ballot_box_with_check:       | Multimedia profiling.                                                                                                                   |
| `mtkdcs`                    | :negative_squared_cross_mark: |                                                                                                                                         |
| `mtprof`                    | :ballot_box_with_check:       | Kernel and boot profiling utilities.                                                                                                    |
| `mu3d`                      | :ballot_box_with_check:       | USB 3.0 MAC                                                                                                                             |
| `mu3phy`                    | :ballot_box_with_check:       | USB 3.0 PHY                                                                                                                             |
| `multibridge`               | :negative_squared_cross_mark: |                                                                                                                                         |
| `nand`                      | :negative_squared_cross_mark: |                                                                                                                                         |
| `nfc`                       | :negative_squared_cross_mark: |                                                                                                                                         |
| `partition`                 | :ballot_box_with_check:       | Support for GPT (GUID) partititons on `mmcblk0`. `mmc` driver references this, to find `otp`, `userdata`, and `cache` partitions.       |
| `pd`                        | :negative_squared_cross_mark: | USB power delivery                                                                                                                      |
| `pdr_sensor`                | :negative_squared_cross_mark: |                                                                                                                                         |
| `pedometer`                 | :negative_squared_cross_mark: |                                                                                                                                         |
| `performance`               | :negative_squared_cross_mark: |                                                                                                                                         |
| `pick_up_sensor`            | :negative_squared_cross_mark: |                                                                                                                                         |
| `pmic`                      | :negative_squared_cross_mark: | Power Management Interface Chip, "new architectur". Gemini seems to use the old architecture.                                           |
| `pmic_wrap`                 | :ballot_box_with_check:       | Connection to the PMIC.                                                                                                                 |
| `power`                     | :ballot_box_with_check:       | A huge driver for power-management.                                                                                                     |
| `power_gs`                  | :negative_squared_cross_mark: |                                                                                                                                         |
| `pwm`                       | :ballot_box_with_check:       |                                                                                                                                         |
| `ram_console`               | :ballot_box_with_check:       | Logs debug info into RAM, can be read after a reboot.                                                                                   |
| `rotationvector`            | :negative_squared_cross_mark: |                                                                                                                                         |
| `rrc`                       | :negative_squared_cross_mark: | Adaptive refresh rate                                                                                                                   |
| `rtc`                       | :ballot_box_with_check:       | Real-time clock. Uses the MT6351 version of the driver.                                                                                 |
| `rt-regmap`                 | :negative_squared_cross_mark: |                                                                                                                                         |
| `sched`                     | :ballot_box_with_check:       | Something related to big.LITTLE clustering.                                                                                             |
| `scp`                       | :ballot_box_with_check:       | MediaTek's custom DSP                                                                                                                   |
| `secmem`                    | :negative_squared_cross_mark: | Requires Trustonic TEE.                                                                                                                 |
| `secwidevine`               | :negative_squared_cross_mark: | Some video DRM thing. Requires Trustonic TEE.                                                                                           |
| `selinux_warning`           | :negative_squared_cross_mark: |                                                                                                                                         |
| `sensor_bio`                | :negative_squared_cross_mark: | Alternative drivers for sensors, using some BIO (Boosted I/O) I/O system instead of IIO.                                                |
| `sensorHub`                 | :negative_squared_cross_mark: |                                                                                                                                         |
| `shake_sensor`              | :negative_squared_cross_mark: |                                                                                                                                         |
| `smartpa`                   | :negative_squared_cross_mark: | Not referenced from the main Makefile.                                                                                                  |
| `smi`                       | :ballot_box_with_check:       | A bus-bandwidth control driver for video and JPEG encoding/decoding.                                                                    |
| `ssusb`                     | :negative_squared_cross_mark: | Another custom USB 3.0 driver.                                                                                                          |
| `ssw`                       | :negative_squared_cross_mark: | SIM switcher.                                                                                                                           |
| `step_counter`              | :ballot_box_with_check:       | BMI160 bases step counter.                                                                                                              |
| `sync`                      | :ballot_box_with_check:       | Provides synchronization primitives for other drivers.                                                                                  |
| `sysenv`                    | :ballot_box_with_check:       | Sending environment variables to use space with a netlink socket?                                                                       |
| `systracker`                | :negative_squared_cross_mark: | A hardware debugger.                                                                                                                    |
| `teei`                      | :negative_squared_cross_mark: | MicroTrust trusted execution environment driver.                                                                                        |
| `thermal`                   | :ballot_box_with_check:       |                                                                                                                                         |
| `tilt_detector_sensor`      | :negative_squared_cross_mark: |                                                                                                                                         |
| `trustzone`                 | :negative_squared_cross_mark: |                                                                                                                                         |
| `uart`                      | :ballot_box_with_check:       | MediaTek's extensions to 8250. Exists in mainline.                                                                                      |
| `uncali_acc`                | :negative_squared_cross_mark: |                                                                                                                                         |
| `uncali_gyro`               | :negative_squared_cross_mark: |                                                                                                                                         |
| `uncali_mag`                | :negative_squared_cross_mark: |                                                                                                                                         |
| `usb11`                     | :ballot_box_with_check:       | A modified version of the MUSB OTG driver, which exists in mainline. Enabled on the Gemini.                                             |
| `usb20`                     | :negative_squared_cross_mark: |                                                                                                                                         |
| `usb2jtag`                  | :negative_squared_cross_mark: |                                                                                                                                         |
| `usb_boost`                 | :ballot_box_with_check:       |                                                                                                                                         |
| `usb_c`                     | :ballot_box_with_check:       | USB-C detection and switching (not HCI).                                                                                                |
| `vibrator`                  | :ballot_box_with_check:       | Controls the vibrator via the PMIC. Enabled on the Gemini.                                                                              |
| `video`                     | :ballot_box_with_check:       | The framebuffer driver.                                                                                                                 |
| `videocodec`                | :ballot_box_with_check:       | Video encoder/decoder. Compatible with `mediatek,mt6797-venc` and `mediatek,mt6797-vdec`.                                               |
| `vow`                       | :ballot_box_with_check:       | Voice Wakeup.                                                                                                                           |
| `wake_gesture_sensor`       | :negative_squared_cross_mark: |                                                                                                                                         |
| `watchpoint`                | :negative_squared_cross_mark: | Hardware memory access breakpoints.                                                                                                     |
| `wmt_ccci`                  | :negative_squared_cross_mark: | Configures the Wireless Managemenet Task.                                                                                               |
| `xhci`                      | :ballot_box_with_check:       | MediaTek's custom xHCI driver.                                                                                                          |
| `zone_movable_cma`          | :negative_squared_cross_mark: | Related to video playback.                                                                                                              |
