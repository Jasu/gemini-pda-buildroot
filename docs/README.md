# Documentation and notes about the Gemini PDA

## Notes

- [Notes about MT6797 support in the original Android kernel](ANDROID-KERNEL.md)
- [Notes about the MT6797 device tree in the original Android kernel](ANDROID-MT6797-DTS.md)
- [Notes about the boot process](BOOT.md)
- [Notes about the USB UART](USB-UART.md)
- [Notes about the LCD](LCD.md)
- [Notes about system clocks](CLOCKS.md)
- [Undocumented registers](UNDOCUMENTED-REGISTERS.md)
- [SMI LARB ports](SMI-LARB.md)
- [MediaTek slang dictionary](GLOSSARY.md)

## External resources

- [MT6797 Operational specification](https://www.96boards.org/documentation/consumer/mediatekx20/additional-docs/docs/MT6797_Functional_Specification_V1_0.pdf)  
  Like a datasheet. Contains clock and register specifications etc. Note that
  the actual CPU is MT6797X, not MT6797, but they only differ in clock speeds,
  dual camera support, and support for "MiraVision's EnergySmart Screen
  technology".
- [Linux MediaTek mailing list archives](http://lists.infradead.org/pipermail/linux-mediatek/)
- [Linux MediaTek patchwork](https://patchwork.kernel.org/project/linux-mediatek/list/)
- [Omegamoon blog - MediaTek USB-UART on Gemini-PDA](http://www.omegamoon.com/blog/index.php?entry=entry180626-210224)

## External resources not directly relevant

These resources are not used in this project, but might prove useful.

- [MediaTek bootloader and firmware utilities](https://github.com/mtek-hack-hack)
- [postmarketOS's attempt to replace MediaTek bootloader](https://postmarketos.org/blog/2018/04/14/lowlevel/)
- [Comsecuris blog about a vulnerability in MediaTek's baseband communication interface (CCCI)](https://comsecuris.com/blog/posts/path_of_least_resistance/)
