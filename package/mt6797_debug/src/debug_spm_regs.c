// SPDX-License-Identifier: GPL-2.0

#include <linux/kernel.h>
#include <linux/module.h>
#include "regdump.h"

#define SPM_BASE 0x10006000

DEFINE_REGISTER(PWR_STATUS, 0x180, "SPM power status",
	REGISTER_BIT_ON(0, "MD1 (modem 1)"),
	REGISTER_BIT_ON(1, "CONN (connectivity system)"),
	REGISTER_BIT_ON(2, "DPY"),
	REGISTER_BIT_ON(3, "DIS (display)"),
	REGISTER_BIT_ON(4, "DPY CH1"),
	REGISTER_BIT_ON(5, "ISP (imaging)"),
	REGISTER_BIT_ON(6, "IFR"),
	REGISTER_BIT_ON(7, "VDE (video decoding)"),
	REGISTER_BIT_ON(8, "MFG (Mali) core 3"),
	REGISTER_BIT_ON(9, "MFG (Mali) core 2"),
	REGISTER_BIT_ON(10, "MFG (Mali) core 1"),
	REGISTER_BIT_ON(11, "MFG (Mali) core 0"),
	REGISTER_BIT_ON(12, "MFG (Mali)"),
	REGISTER_BIT_ON(13, "MFG (Mali) async"),
	REGISTER_BIT_ON(20, "MJC (MiraVision)"),
	REGISTER_BIT_ON(21, "VEN (video encoding)"),
	REGISTER_BIT_ON(24, "Audio"),
	REGISTER_BIT_ON(28, "C2K (modem 2)")
);

DEFINE_REGISTER(PWR_STATUS_2ND, 0x184, "SPM power status 2",
	REGISTER_BIT_ON(0, "MD1 (modem 1)"),
	REGISTER_BIT_ON(1, "CONN (connectivity system)"),
	REGISTER_BIT_ON(2, "DPY"),
	REGISTER_BIT_ON(3, "DIS (display)"),
	REGISTER_BIT_ON(4, "DPY CH1"),
	REGISTER_BIT_ON(5, "ISP (imaging)"),
	REGISTER_BIT_ON(6, "IFR"),
	REGISTER_BIT_ON(7, "VDE (video decoding)"),
	REGISTER_BIT_ON(8, "MFG (Mali) core 3"),
	REGISTER_BIT_ON(9, "MFG (Mali) core 2"),
	REGISTER_BIT_ON(10, "MFG (Mali) core 1"),
	REGISTER_BIT_ON(11, "MFG (Mali) core 0"),
	REGISTER_BIT_ON(12, "MFG (Mali)"),
	REGISTER_BIT_ON(13, "MFG (Mali) async"),
	REGISTER_BIT_ON(20, "MJC (MiraVision)"),
	REGISTER_BIT_ON(21, "VEN (video encoding)"),
	REGISTER_BIT_ON(24, "Audio"),
	REGISTER_BIT_ON(28, "C2K (modem 2)")
);

#define DEFINE_PWR_CON_REGISTER(name_, offset_, desc_, ...) \
	DEFINE_REGISTER(name_, offset_, desc_" power control", \
		REGISTER_BIT_SET(0, "Power reset"), \
		REGISTER_BIT_SET(1, "Power ISO"), \
		REGISTER_BIT_SET(2, "Power on"), \
		REGISTER_BIT_SET(3, "Power on 2nd"), \
		REGISTER_BIT_DISABLED(4, "Clock"), \
		##__VA_ARGS__ \
	)

DEFINE_PWR_CON_REGISTER(VEN_PWR_CON, 0x304, "VEN (video encoder)",
	REGISTER_FIELD(8, 11, "Power down requested"),
	REGISTER_FIELD(12, 15, "Power down ACK")
);
DEFINE_PWR_CON_REGISTER(ISP_PWR_CON, 0x308, "ISP (imaging)",
	REGISTER_FIELD(8, 9, "Power down requested"),
	REGISTER_FIELD(12, 13, "Power down ACK")
);
DEFINE_PWR_CON_REGISTER(DIS_PWR_CON, 0x30C, "DIS (display)",
	REGISTER_BIT(8, "Power down requested", "Power down not requested"),
	REGISTER_BIT_ACK(12, "Power down")
);
DEFINE_PWR_CON_REGISTER(AUDIO_PWR_CON, 0x314, "Audio",
	REGISTER_FIELD(8, 11, "Power down requested"),
	REGISTER_FIELD(12, 15, "Power down ACK"),
	REGISTER_FIELD(16, 17, "MD32 ISOINT B"),
	REGISTER_FIELD(20, 21, "MD32 Sleep B"),
	REGISTER_FIELD(24, 25, "MD32 power down requested"),
	REGISTER_FIELD(28, 29, "MD32 power down ACK")
);
DEFINE_PWR_CON_REGISTER(IFR_PWR_CON, 0x318, "IFR",
	REGISTER_FIELD(8, 11, "Power down requested"),
	REGISTER_FIELD(12, 15, "Power down ACK"),
	REGISTER_FIELD(16, 19, "ISOINT B"),
	REGISTER_FIELD(20, 23, "Sleep B"),
	REGISTER_FIELD(24, 27, "CKISO")
);

DEFINE_PWR_CON_REGISTER(DPY_PWR_CON, 0x31C, "DPY");
DEFINE_PWR_CON_REGISTER(DPY_CH1_PWR_CON, 0x31C, "DPY CH1");
DEFINE_PWR_CON_REGISTER(MD1_PWR_CON, 0x320, "MD1",
	REGISTER_BIT(8, "Power down requested", "Power down not requested")
);
DEFINE_PWR_CON_REGISTER(MD2_PWR_CON, 0x324, "MD2",
	REGISTER_BIT(8, "Power down requested", "Power down not requested")
);
DEFINE_PWR_CON_REGISTER(C2K_PWR_CON, 0x328, "C2K",
	REGISTER_BIT(8, "Power down requested", "Power down not requested")
);
DEFINE_PWR_CON_REGISTER(CONN_PWR_CON, 0x32C, "Connectivity",
	REGISTER_BIT(8, "Power down requested", "Power down not requested"),
	REGISTER_BIT_ACK(12, "Power down")
);
DEFINE_PWR_CON_REGISTER(VCOREPDN_PWR_CON, 0x330, "VCOREPDN");
DEFINE_PWR_CON_REGISTER(MFG_ASYNC_PWR_CON, 0x334, "MFG (Mali) async");
DEFINE_PWR_CON_REGISTER(MFG_PWR_CON, 0x338, "MFG (Mali)");
DEFINE_PWR_CON_REGISTER(MFG_CORE0_PWR_CON, 0x340, "MFG (Mali) core 0");
DEFINE_PWR_CON_REGISTER(MFG_CORE1_PWR_CON, 0x344, "MFG (Mali) core 1");
DEFINE_PWR_CON_REGISTER(MFG_CORE2_PWR_CON, 0x348, "MFG (Mali) core 2");
DEFINE_PWR_CON_REGISTER(MFG_CORE3_PWR_CON, 0x34C, "MFG (Mali) core 3");
DEFINE_PWR_CON_REGISTER(VDE_PWR_CON, 0x300, "VDE (video decoder)",
	REGISTER_BIT(8, "Power down requested", "Power down not requested"),
	REGISTER_BIT_ACK(12, "Power down")
);
DEFINE_REGISTER(MFG_SRAM_CON, 0x33C, "MFG (Mali) SRAM status",
		REGISTER_FIELD(0, 3, "MFG power down requested"),
		REGISTER_FIELD(4, 7, "MFG CKISO"),
		REGISTER_FIELD(8, 11, "MFG sleep B"),
		REGISTER_FIELD(12, 15, "MFG ISOINT B"),
		REGISTER_BIT_ACK(16, "MFG power down"),
		REGISTER_BIT_ACK(20, "Core 0 power down"),
		REGISTER_BIT_ACK(21, "Core 1 power down"),
		REGISTER_BIT_ACK(22, "Core 2 power down"),
		REGISTER_BIT_ACK(23, "Core 3 power down")
);

void __init mt6797_debug_spm_regs_init(struct dentry *regs_dir)
{
	regs_dir = debugfs_create_dir("spm", regs_dir);

	REGISTER_FILE(regs_dir, SPM_BASE, PWR_STATUS);
	REGISTER_FILE(regs_dir, SPM_BASE, MFG_ASYNC_PWR_CON);
	REGISTER_FILE(regs_dir, SPM_BASE, MFG_PWR_CON);
	REGISTER_FILE(regs_dir, SPM_BASE, MFG_CORE0_PWR_CON);
	REGISTER_FILE(regs_dir, SPM_BASE, MFG_CORE1_PWR_CON);
	REGISTER_FILE(regs_dir, SPM_BASE, MFG_CORE2_PWR_CON);
	REGISTER_FILE(regs_dir, SPM_BASE, MFG_CORE3_PWR_CON);
	REGISTER_FILE(regs_dir, SPM_BASE, VDE_PWR_CON);
	REGISTER_FILE(regs_dir, SPM_BASE, VEN_PWR_CON);
	REGISTER_FILE(regs_dir, SPM_BASE, ISP_PWR_CON);
	REGISTER_FILE(regs_dir, SPM_BASE, DIS_PWR_CON);
	REGISTER_FILE(regs_dir, SPM_BASE, AUDIO_PWR_CON);
	REGISTER_FILE(regs_dir, SPM_BASE, IFR_PWR_CON);
	REGISTER_FILE(regs_dir, SPM_BASE, DPY_PWR_CON);
	REGISTER_FILE(regs_dir, SPM_BASE, DPY_CH1_PWR_CON);
	REGISTER_FILE(regs_dir, SPM_BASE, MD1_PWR_CON);
	REGISTER_FILE(regs_dir, SPM_BASE, MD2_PWR_CON);
	REGISTER_FILE(regs_dir, SPM_BASE, C2K_PWR_CON);
	REGISTER_FILE(regs_dir, SPM_BASE, MFG_SRAM_CON);
}
