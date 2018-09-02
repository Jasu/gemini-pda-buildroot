// SPDX-License-Identifier: GPL-2.0

#include <linux/kernel.h>
#include <linux/module.h>
#include "regdump.h"

#define USB_SIFSLV_U2PHY_BASE 0x11210800
#define SSUSB_SIFSLV_U2PHY_BASE 0x11280800
#define SSUSB_SIF2SLV_U2PHY_BASE 0x11290800

#define DEFINE_USB_SIF(prefix_, name_prefix_) \
	DEFINE_REGISTER(prefix_##_USBPHYACR6, 0x018, #name_prefix_" PHYACR 6", \
		REGISTER_ENUM(0, 3, "RG_USB20_SQTH SQ threshold", \
			"85mV", \
			"90mV", \
			"95mV", \
			"100mV", \
			"105mV", \
			"110mV", \
			"115mV", \
			"120mV", \
			"125mV", \
			"130mV", \
			"135mV", \
			"140mV", \
			"145mV", \
			"150mV", \
			"155mV", \
			"160mV" \
		), \
		REGISTER_ENUM(4, 7, "RG_USB20_DISCT Disconnect threshold", \
			"400mV", \
			"420mV", \
			"440mV", \
			"460mV", \
			"480mV", \
			"500mV", \
			"520mV", \
			"540mV", \
			"560mV", \
			"580mV", \
			"600mV", \
			"620mV", \
			"640mV", \
			"660mV", \
			"680mV", \
			"700mV" \
		), \
		REGISTER_BIT_ENABLED(8, "RG_USB20_HSRX_TMODE."), \
		REGISTER_ENUM(9, 10, "BIAS_EN_SEL", \
			"ENPLL (always on)" \
			"IDLEB | RCV_EN (when TX on, RX off, device mode only)" \
			"!ENPLL | FS_BIAS_EN (keep high in HS mode)" \
			"RG_USB20_HSRX_TMODE_EN"), \
		REGISTER_ENUM(12, 13, "RG_USB20_HSRX_MMODE_SELE Selects HS_RX manual mode", \
			"HS_RX in normal mode, switch SQ/DISC function", \
			"Manual mode, switch SQ (IDLEB=0)/DISC", \
			"Force HS_RX in SQ mode", \
			"Force HS_RX in DISC mode" \
		), \
		REGISTER_ENUM(16, 18, "RG_USB20_OTG_ABIST_SELE Selects OTG ABIST voltage", \
			"100mV", \
			"200mV", \
			"350mV", \
			"450mV", \
			"700mV", \
			"800mV", \
			"1400mV", \
			"1600mV" \
		), \
		REGISTER_BIT_ENABLED(19, \
			"RG_USB20_OTG_ABIST_EN OTG ABIST mode signal"), \
		REGISTER_BIT_ENABLED(20, "RG_USB20_OTG_VBUSCMP_EN OTG"), \
		REGISTER_BIT(22, \
			"RG_USB20_SR_CLK_SEL 240MHz for ABIST clock", \
			"RG_USB20_SR_CLK_SEL Slew rate calibration clock"), \
		REGISTER_BIT_ENABLED(23, "RG_USB20_BC11_SW_EN BC1.1 switch control"), \
		REGISTER_FIELD(24, 31, "RG_USB20_PHY_REV Reserves INT PHY") \
	); \
	DEFINE_REGISTER(prefix_##_U2PHYACR4, 0x020, #name_prefix_"PHYA Control 4 Register", \
		REGISTER_FIELD(0, 1, "HS_RCV_EN_MODE"), \
		REGISTER_FIELD(2, 3, "HS_SQ_EN_MODE"), \
		REGISTER_BIT_SET(4, "TX_VCMPDN_EN"), \
		REGISTER_BIT_SET(5, "TX_BIAS_EN"), \
		REGISTER_BIT_ENABLED(8, "GPIO Mode control"), \
		REGISTER_BIT(9, "GPIO control by system register", \
			"GPIO control by USB PHY register"), \
		REGISTER_BIT_ENABLED(12, "GPIO DP output"), \
		REGISTER_BIT_ENABLED(13, "GPIO DM output"), \
		REGISTER_BIT_SET(14, "GPIO DP input"), \
		REGISTER_BIT_SET(15, "GPIO DM input"), \
		REGISTER_BIT_ENABLED(16, "DP 100k"), \
		REGISTER_BIT_ENABLED(17, "DM 100k"), \
		REGISTER_BIT_ON(18, "DP 100k mode") \
	); \
	DEFINE_REGISTER(prefix_##_U2PHYDTM0, 0x068, #name_prefix_"PHYD Control UTMI 0 Register", \
		REGISTER_FIELD(0, 1, "OPMODE for bypass PHY UTMI signals"), \
		REGISTER_BIT_ENABLED(2, "Bypass PHY UTMI signal TERMSEL"), \
		REGISTER_BIT_ENABLED(3, "Bypass PHY UTMI signal SUSPENDM"), \
		REGISTER_FIELD(4, 5, "Bypass PHY UTMI signal XCVRSEL"), \
		REGISTER_BIT_ENABLED(6, "Bypass PHY UTMI signal DPPULLDOWN"), \
		REGISTER_BIT_ENABLED(7, "Bypass PHY UTMI signal DMPULLDOWN"), \
		REGISTER_BIT_ENABLED(8, "Bypass PHY UTMI signal TXVALID"), \
		REGISTER_BIT_ENABLED(9, "Bypass PHY UTMI signal TXVALIDH"), \
		REGISTER_FIELD(10, 13, "Bypass PHY UTMI signal DATA_IN"), \
		REGISTER_BIT_SET(14, "PHY UTMI soft reset"), \
		REGISTER_BIT_ENABLED(15, \
			"Force PHY UTMI signals to values specified"), \
		REGISTER_BIT_SET(16, \
			"Forced value of PHY UTMI signal OPMODE"), \
		REGISTER_BIT_SET(17, \
		       	"Forced value of PHY UTMI signal TERMSEL"), \
		REGISTER_BIT_SET(18, \
			"Forced value of PHY UTMI signal SUSPENDM"), \
		REGISTER_BIT_SET(19, \
			"Forced value of PHY UTMI signal XCVRSEL"), \
		REGISTER_BIT_SET(20, \
			"Forced value of PHY UTMI signal DPPULLDOWN"), \
		REGISTER_BIT_SET(21, \
			"Forced value of PHY UTMI signal DMPULLDOWN"), \
		REGISTER_BIT_SET(22, \
			"Forced value of PHY UTMI signal TXVALID"), \
		REGISTER_BIT_SET(23, \
			"Forced value of PHY UTMI signal DATAIN"), \
		REGISTER_BIT_SET(24, \
			"Forced value of PHY UTMI signal DRVBUS"), \
		REGISTER_BIT_SET(25, \
			"Forced value of PHY UTMI signal USB_CLKEN"), \
		REGISTER_BIT_SET(26, \
			"Forced value of PHY UTMI signal UART_EN"), \
		REGISTER_BIT_SET(27, \
			"Forced value of PHY UTMI signal UART_TX_OE)"), \
		REGISTER_BIT_SET(28, \
			"Forced value of PHY UTMI signal UART_BIAS_EN"), \
		REGISTER_BIT_SET(29, \
			"Forced value of PHY UTMI signal UART_I"), \
		REGISTER_ENUM(30, 31, "UART mode, RG_DP_100K_EN", \
			"RG_DP_100K_EN = DA_USB_UART_EN", \
			"RG_DP_100K_EN = DA_USB_UART_EN & ~DA_USB_UART_TX_OE", \
			"RG_DP_100K_EN = 0", \
			"RG_DP_100K_EN = 1" \
		) \
	); \
	DEFINE_REGISTER(prefix_##_U2PHYDTM1, 0x06C, #name_prefix_"PHYD Control UTMI 1 Register", \
		REGISTER_BIT_ENABLED(0, "Bypass PHY UTMI signal IDPULLUP"), \
		REGISTER_BIT_ENABLED(1, "Bypass PHY UTMI signal IDDIG"), \
		REGISTER_BIT_ENABLED(2, "Bypass PHY UTMI signal AVALID"), \
		REGISTER_BIT_ENABLED(3, "Bypass PHY UTMI signal BVALID"), \
		REGISTER_BIT_ENABLED(4, "Bypass PHY UTMI signal SESSEND"), \
		REGISTER_BIT_ENABLED(5, "Bypass PHY UTMI signal VBUSVALID"), \
		REGISTER_BIT_SET(8, \
			"Forced value of PHY UTMI signal IDPULLUP"), \
		REGISTER_BIT_SET(9, \
			"Forced value of PHY UTMI signal IDDIG"), \
		REGISTER_BIT_SET(10, \
			"Forced value of PHY UTMI signal AVALID"), \
		REGISTER_BIT_SET(11, \
			"Forced value of PHY UTMI signal BVALID"), \
		REGISTER_BIT_SET(12, \
			"Forced value of PHY UTMI signal SESSEND"), \
		REGISTER_BIT_SET(13, \
			"Forced value of PHY UTMI signal VBUSVALID"), \
		REGISTER_BIT_ENABLED(16, "Bypass PHY UTMI signal UART_EN"), \
		REGISTER_BIT_ENABLED(17, "Bypass PHY UTMI signal UART_TX_OE"), \
		REGISTER_BIT_ENABLED(18, "Bypass PHY UTMI signal UART_BIAS_EN"), \
		REGISTER_BIT_ENABLED(19, "Bypass PHY UTMI signal UART_I"), \
		REGISTER_BIT_ENABLED(22, "MAC 60MHz clock"), \
		REGISTER_BIT_ENABLED(23, "MAC 48MHz clock"), \
		REGISTER_FIELD(24, 29, "On-chip PRBS7 decoder bit count"), \
		REGISTER_BIT_ENABLED(31, "On-chip PRBS7 decoder") \
	)

DEFINE_USB_SIF(USB, "USB 2.0 SIF ");
// Registers for U3D SIFs are not documented in the register tables.
DEFINE_USB_SIF(U3D, "SSUSB 3.0 SIF 1 ");
DEFINE_USB_SIF(U3D_2, "SSUSB 3.0 SIF 2 ");

void __init mt6797_debug_usb_sifslv_u2phy_init(struct dentry * regs_dir)
{
	regs_dir = debugfs_create_dir("usb_sifslv_u2phy", regs_dir);
	REGISTER_FILE(regs_dir, USB_SIFSLV_U2PHY_BASE, USB_U2PHYACR4);
	REGISTER_FILE(regs_dir, USB_SIFSLV_U2PHY_BASE, USB_USBPHYACR6);
	REGISTER_FILE(regs_dir, USB_SIFSLV_U2PHY_BASE, USB_U2PHYDTM0);
	REGISTER_FILE(regs_dir, USB_SIFSLV_U2PHY_BASE, USB_U2PHYDTM1);

	REGISTER_FILE(regs_dir, SSUSB_SIFSLV_U2PHY_BASE, U3D_U2PHYACR4);
	REGISTER_FILE(regs_dir, SSUSB_SIFSLV_U2PHY_BASE, U3D_USBPHYACR6);
	REGISTER_FILE(regs_dir, SSUSB_SIFSLV_U2PHY_BASE, U3D_U2PHYDTM0);
	REGISTER_FILE(regs_dir, SSUSB_SIFSLV_U2PHY_BASE, U3D_U2PHYDTM1);

	REGISTER_FILE(regs_dir, SSUSB_SIF2SLV_U2PHY_BASE, U3D_2_U2PHYACR4);
	REGISTER_FILE(regs_dir, SSUSB_SIF2SLV_U2PHY_BASE, U3D_2_USBPHYACR6);
	REGISTER_FILE(regs_dir, SSUSB_SIF2SLV_U2PHY_BASE, U3D_2_U2PHYDTM0);
	REGISTER_FILE(regs_dir, SSUSB_SIF2SLV_U2PHY_BASE, U3D_2_U2PHYDTM1);
}
