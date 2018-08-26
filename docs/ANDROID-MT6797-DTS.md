# Notes about the MT6797 device tree in the original Android kernel

This file is highly incomplete.

- The DTB is appended to the boot image in a non-standard way. The appended
  file is not seen by `binwalk`.
- On Android, the DTS file used is `aeon6797_6m_n.dts`.
- **NOTE:** The device file `mt67977.dtsi` is wildly different from mainline.

### Nodes

#### `soc/i2c@11007000`

Seems to have power / GPIO -related chips. Only nodes:

- `bq24261`: Texas Instruments battery charger chip.
- `mediatek,mt6306`: GPIO controller? Referred to in HDMI, camera, connectivity

#### `soc/mmc0`, `soc/mmc1`

- Seems to be a standard `mmc` drivers.

#### `soc/led*`

The `soc/led` devices are likely to be wrong, since

- The bootloader cannot find LEDs in boot
- There is no jogball backlight, button backlight etc.
- LCD backlight is also defined in the LCM controller's driver.

| Number | Name                          | Note                                                                                                                |
| ------ | ----------------------------- | ------------------------------------------------------------------------------------------------------------------- |
| 0      | `mediatek,red`                |                                                                                                                     |
| 1      | `mediatek,green`              |                                                                                                                     |
| 2      | `mediatek,blue`               |                                                                                                                     |
| 3      | `mediatek,jogball-backlight`  |                                                                                                                     |
| 4      | `mediatek,keyboard-backlight` |                                                                                                                     |
| 5      | `mediatek,button-backlight`   |                                                                                                                     |
| 6      | `mediatek,lcd-backlight`      | Probably not the real LCD backlight, backlight referred to in LCM include as well, and most LEDs seem to be unused. |

### `soc/vibrator0`

- Mediatek-specific vibrator driver, controlled by `drivers/misc/mediatek/vibrator`.
- Controlled over PMIC - could be a good testing point for PMIC.

### `soc/cust_accel@0`, `soc/cust_gyro@0`

- iNEMO LSM6DS3 accelerometer + gyro
- Supported in mainline, `iio/imu/st_lsm6dsx`
- **TODO:** Which one, BMI160 or LSM6DS3 is actually used, if any?

### `soc/cust_accel@1`, `soc/cust_gyro@1`

- Bosch Sensortec BMI160 accelerometer + gyro
- Supported in mainline, `drivers/iio/imu/bmi160`
- **TODO:** Which one, BMI160 or LSM6DS3 is actually used, if any?

### `soc/cust_alsps@0`

- Ambient light sensor.
- MAYBE in mainline - only `STK3310` and `STK3311` are supported. **TODO:**
  Which version does the Gemini have?

### `soc/cust_mag@0`

- MMC3530 magnetometer
- Not in mainline, but MMC35240 is.

### `soc/cust_baro@0`

- Bosch Sensortec BMP280 barometer
- Supported in mainline, see `drivers/iio/pressure/bmp280.h`

### `soc/cust_hmdy@0`

- ST Microelectronics HTS221 capacitive humidity sensor
- Supported in mainline, see `drivers/iio/humidity/hts221_i2c.c`

### MT6797: `soc/ext_buck_vproc`, `&pio/da9214_gpio_default`

- Dialog Semiconductor DA9214 power regulator / power supply chip
- Used for CPU power supply.
- `arch/arm64/kernel/psci.c` is patched to use it.
- **NOTE:** Pins set in the aeon DTS.

### MT6797: `soc/scpdvfs`, `soc/scp`

- Some Mediatek-specific DSP
- `soc/scp` disabled in DTS, maybe enabled by the bootloader?
- Mainline DTS has `scpsys`

### MT6797: `soc/emi_mpu`, `soc/mdhw_smi`

- Some memory-protection unit? EMI = external memory interface?
- Referred to from `scp`, `connectivity`, `mtkdcs`, `devapc`, `usb11`, `secmem`,
  `eccci`, `video`... basically from everywhere.

### MT6797: `soc/infracfg`

- Controls clocks and resets?
- Bus access protection?
- Exists in mainline. Mainline DTS has `infrasys`.

### MT6797: `soc/sramrom`

- No driver in tree?
- Perhaps it's read by the bootloader?

### MT6797: `soc/emi`

- Digital clock manager
- Also related to DRAM refresh? referred to from `dramc`.

### MT6797: `soc/sys_cirq`

- IRQ controller

### MT6797: `soc/m4u`

> "M4U driver support for multimedia hardware use non-physical continuous memory."

- Referred to from `ext_disp`, `smi`, `arch/arm64/mm/mt_innercache.c`,
  `mtk_iommu`, `cmdq`, `power`, `video` (including dispsys), `cameraisp`

### MT6797: `soc/efusec`

- Referred to in power, short for efuse control?

### MT6797: `soc/devapc`

- Enabled via `CONFIG_MTK_DEVAPC_DRIVER`
> APC is a kernel driver controlling internal device security

### MT6797: `soc/ddrphy`, `soc/ddrphy_a`, `soc/ddrphy_c`, `soc/ddrphy_d`, `soc/dramc_nao`, `soc_dramc_b_nao`

- Referred to in `power` and `dramc`
- Some DRAM refresh thing?
- `CONFIG_MTK_DRAMC`, enabled in defconfig


### MT6797: `soc/keypad`

- `keyboard`
- `CONFIG_KEYBOARD_MTK`, enabled in defconfig

### MT6797: `soc/bat_metter`

- In `power`
- Configuration contains charging voltage, temperature etc. info.
- `CONFIG_MTK_SMART_BATTERY`, enabled in defconfig

### MT6797: `soc/mcumixed`, `soc/mcufhctl`

- Used in `freqhopping`
- `CONFIG_MTK_FREQ_HOPPING` enabled in defconfig
- Referred to in `mt_gpufreq`, but not used due to a typo in
  `#ifdef CONFIG_MTK_FREQ_HOPPIN`

### MT6797: `soc/aes_top0`, `soc/aes_top1`

- Only referred to in configs and clocks, not used?
- Freecores has some AES core with the same name: https://github.com/freecores/aes_pipe/blob/master/rtl/vhdl/aes_top.vhdl


### MT6797: `soc/modem_temp`

- Referred to only from `power`

### MT6797: `soc/bus_dbg`

- Referred to from `systracker`
> SYSTRACKER is a hardware debugger


### MT6797: `soc/c2kmisc`, `soc/ap_ccif0`, `soc/ap_ccif1`, `soc/md_ccif0`, `soc/md_ccif1`, `soc/ap2c2k_ccif`, `soc/md2md_md1_ccif`, `soc/ap_cldma`, `soc/md_cldma`, `soc/dbgapb`, `soc/met_cci400`

- Related to modem
- **NOTE:** `dvb-usb` contains constants with `_ccif_` in their name.

### MT6797: `soc/infra_mbist`

- Not referred to from anywhere, maybe used by the bootloader?

### MT6797: `soc/infra_trng`

- Only referred to in clocks.

### MT6797: `soc/gcpu`, `soc/gcpu_rsa`

- Some cryptographic co-processor?
- `CONFIG_TRUSTONIC_TEE_SUPPORT` is not set in defconfig.
- `soc/gcpu_rsa` not referred to from anywhere.

### MT6797: `soc/gce`

- Related to `cmdq`

### MT6797: `soc/cqdma`

- Looks like a generic DMA driver, but name related to the command queue?
- Not referred to from anywhere?

### MT6797: `soc/mipi_tx0`, `soc/mipi_tx1`

- Referred to from `video/mt6797/dispsys/`
- MIPI is a protocol for transmitting the data stream to/from displays, cameras, etc.

### MT6797: `soc/mipi_rx_ana_csi0`, `soc/mipi_rx_ana_csi1`

- Not used?

### MT6797: `soc/vad`

- Not used?

### MT6797: `soc/lastpc`, `soc/lastbus`

- Debugging thing for last program counter position and last bus access?
- In `debuglatch`

### MT6797: `soc/cpuxgpt`

- General-purpose timer
- Declared as `CLOCKSOURCE`

### MT6797: `soc/mcucfg`

- Referred to in `power` and `eccci`

### MT6797: `soc/ocp_cfg`

- Referred to in `power`
- Seems to control CPU voltage (`mt_ocp.c` refers to clusters in comments)

### MT6797: `soc/ptp3_idvfs`, `soc/ptpopt`

- Referred to in `power`
- Controls some clocks and maybe voltages (references to both voltages and PLLs)?

### MT6797: `soc/bpi_bsi_slv0`, `soc/bpi_bsi_slv1`, `soc/bpi_bsi_slv2`

- Referred to in `power`

### MT6797: `soc/gic`

- Some interrupt controller?
- Not looked for with `compatible`, but `irq` seems relevant.
- Included in mainline DTS.

### MT6797: `soc/cpu_dbgapb`

- Hardware watch points (i.e. breakpoints on memory access)

### MT6797: `soc/ap_dma`

- I2C

### MT6797: `soc/btif_tx`, `soc/btif_rx`, `soc/btif`

- Bluetooth? A/D? Referred to from `btif`, which is called from `connectivity`

### MT6797: `soc/auxadc`

- Auxiliary ADC
- Referred to from `eccci` and `dual_ccci` (modems)

### MT6797: `soc/i2c*`

- Self-explanatory

### MT6797: `soc/pwm`

- PWM controller
- Lots of extra logic for `MT6797`
- Referred to in leds and IR transmitter
- **NOTE:** Referred to from aeon GPIO

### MT6797: `soc/spi0`

- Self-explanatory

### MT6797: `soc/therm_ctrl`

- Referred to by `power` and `thermal`
- `connectivity` contains indirect references.

### MT6797: `soc/eem_fsm`

- Referred to by `power`
- Driver contains some GPU frequency constants

### MT6797: `soc/pwm_disp`

- Unused?

### MT6797: `soc/dvfsp`

- Referred to in Mali, `power`

### MT6797: `soc/dvfs_proc2`

- Referred to in Mali


### MT6797: `soc/audiosys`, `soc/audgpio`, `soc/anc_md32`, `soc/mt_soc_*_pcm`, `soc/mt_soc_voice_md1_bt`, `soc/mt_soc_voip_bt_out`, `soc/mt_soc_voip_bt_in`, `soc/mt_soc_voice_md2`, `soc/mt_soc_hp_impedance_pcm`, `soc/mt_soc_codec_name`, `soc/mt_soc_codec_dummy_name`, `soc/mt_soc_routing_dai_name`, `soc/mt_soc_dai_name`, `soc/mt_soc_pcm_voice_ultra`

- Sound stuff
- `anc_md32` is some clock, probably drives audio. Not directly referred by the
  sound driver, but sound driver contains similarly named variables and boot
  sets up the clock based on this.

### MT6797: `soc/sii9022`, `soc/sii9022_hdmi`

- HDMI transmitter
- The DTS includes `sil9024a.dtsi`, which changes parameters for `sii9022`.
  Maybe the actual chip is a 9024a?

### MT6797: `soc/usb1`, `soc/usb1p_sif`

- Maps to `drivers/misc/mediatek/usb11/mt6797/musbfsh_core.c`
- Seems to be based on Mentor Graphics `MUSB OTG` driver, which exists in
  mainline.
- The `_sif` node seems to be unused. Or maybe used by the bootloader?

### MT6797: `soc/usb0:usb3`, `xhci0:usb3_xhci`

- xHCI seems custom

### MT6797: `goodix-fp`

- Goodix fingerprint sensor
- Gemini doesn't have one, so not used.

### MT6797: `fd`

Face detection
