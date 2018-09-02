# Notes about the USB UART

See [Omegamoon blog - MediaTek USB-UART on Gemini-PDA](http://www.omegamoon.com/blog/index.php?entry=entry180626-210224).

- On Android, `ttyMT0` is the default UART visible over USB. It maps to
  `apuart0` in the device tree, with regs starting at `0x11002000`.
- On mainline, the UART is called `uart0` and is visible as `ttyS0`.
- The bootloader passes the UART to the kernel in `atag,meta`. The Android
  kernel initializes it in `mt_boot`, but only if boot mode is `META_BOOT`,
  `ADVMETA_BOOT`, `ATE_FACTORY_BOOT`, or `FACTORY_BOOT`. For the default boot
  (nothing pressed), boot mode is `NORMAL_BOOT`. So, for the default Android
  boot, the UART is not used in the kernel and output stops after the
  bootloader.
- The UART uses a custom driver, which also exists in the mainline kernel.
- `printk.disable_uart=1` is passed to the Android kernel, which disables UART
  printing.

## How is the USB UART enabled in code?

See [force_uart.c](../package/mt6797_debug/src/force_uart.c). To enable the
force UART functionality, run `make menuconfig` and select `Force UART` in 
the External options menu.

The preloader configures the USB UART if it (somehow?) detects an UART cable.

Register maps don't show registers related to the USB UART. However, USB PHY and
UART drivers need to save their state when the device goes to sleep. This
includes USB UART related state. See the following functions in the Android
source to see how it's done:

- `usb_phy_switch_to_uart` in `mu3phy/mt6797/mtk-phy-asic.c` 
- `mtk_uart_usb_rx_sel` in `drivers/misc/mediatek/uart/mt6797/platform_uart.c`
