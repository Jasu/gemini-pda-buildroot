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
