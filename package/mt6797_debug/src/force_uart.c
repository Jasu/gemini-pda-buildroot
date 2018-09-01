// SPDX-License-Identifier: GPL-2.0

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/io.h>
#include <linux/delay.h>

#define SSUSB_SIF2SLV_U2PHY_BASE	0x11290800
#define USBPHYACR6			0x018
#define U2PHYACR4			0x020
#define U2PHYDTM0			0x068
#define U2PHYDTM1			0x06C

#define UART0_BASE			0x11002000
#define UART_RX_SEL			0x0B0

#define GPIO_BASE			0x10005000
#define GPIO_MISC			0x600

#define REG_OR(val_, addr_) do {					\
	u32 value = readl(addr_);					\
	writel(value | (val_), addr_);					\
	} while (0)

#define REG_AND(val_, addr_) do {					\
		u32 value = readl(addr_);				\
		writel(value & (val_), addr_);				\
	} while (0)

#define REG_SETFIELD(mask_, val_, addr_) do {				\
		u32 value = readl(addr_);				\
		writel((value & ~(mask_)) | ((val_) & (mask_)), addr_);	\
	} while (0)

#define REG_CLRBIT(bit_, addr_) REG_AND(~BIT(bit_), addr_)
#define REG_SETBIT(bit_, addr_) REG_OR(BIT(bit_), addr_)

void __init mt6797_debug_force_uart(void)
{
	void __iomem * usb = ioremap_nocache(SSUSB_SIF2SLV_U2PHY_BASE, 0x1000);
	void __iomem * uart0 = ioremap_nocache(UART0_BASE, 0x1000);
	void __iomem * gpio = ioremap_nocache(GPIO_BASE, 0x1000);

	// Android code sets some PMIC voltages here, we don't. Let's just
	// hope that nothing gets fried.

	// Configure USB PHYS for UART.
	// See mtk_uart_usb_rx_sel in Android
	// drivers/misc/mediatek/uart/platform_uart.c
	REG_CLRBIT(23, usb + USBPHYACR6); // RG_USB20_BC11_SW_EN
	REG_SETBIT(18, usb + U2PHYDTM0); // Force SUSPENDM UTMI signal high
	REG_SETBIT(3, usb + U2PHYDTM0); // Bypass SUSPENDM UTMI signal (enable forcing)
	REG_SETFIELD(GENMASK(31,30), BIT(30), usb + U2PHYDTM0); // RG_UART_MODE = 1

	REG_SETBIT(26, usb + U2PHYDTM0); // Force UART EN signal
	REG_SETBIT(28, usb + U2PHYDTM0); // Force UART BIAS EN signal

	REG_SETBIT(16, usb + U2PHYDTM1); // Bypass UART EN signal (enable forcing)
	REG_SETBIT(18, usb + U2PHYDTM1); // Bypass UART BIAS EN signal (enable forcing)

	REG_SETBIT(17, usb + U2PHYACR4); // RG_USB20_DM_100K_EN


	// Enable UART RX on USB
	// This is undocumented, see mtk_uart_usb_rx_sel in Android
	// drivers/misc/mediatek/uart/platform_uart.c
	REG_SETBIT(0, uart0 + UART_RX_SEL);

	// Enable GPIO. This is also undocumented, see usb_phy_switch_to_uart
	// in Android mu3phy/mt6797/mtk-phy-asic.c
	REG_SETBIT(7, gpio + GPIO_MISC);

	iounmap(uart0);
	iounmap(usb);
	iounmap(gpio);
}
