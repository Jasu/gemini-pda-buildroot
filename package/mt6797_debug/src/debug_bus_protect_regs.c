// SPDX-License-Identifier: GPL-2.0

#include <linux/kernel.h>
#include <linux/module.h>
#include "regdump.h"

#define INFRACFG_BASE 0x10001000

DEFINE_REGISTER(INFRA_TOPAXI_PROTECT_EN, 0x220, "Top AXI Protection Control",
	REGISTER_BIT_ENABLED(0, "CCI M1 protection"),
	REGISTER_BIT_ENABLED(1, "MM M0 protection"),
	REGISTER_BIT_ENABLED(2, "MM M1 protection"),
	REGISTER_BIT_ENABLED(3, "MD1 PSMCU protection"),
	REGISTER_BIT_ENABLED(4, "MD1 MDDMA protection"),
	REGISTER_BIT_ENABLED(5, "MD1 MD to AP protection"),
	REGISTER_BIT_ENABLED(6, "MMAPB protection"),
	REGISTER_BIT_ENABLED(7, "AP to MD MD1 protection"),
	REGISTER_BIT_ENABLED(8, "CCI M2 protection"),
	REGISTER_BIT_ENABLED(9, "CCI M0 protection"),
	REGISTER_BIT_ENABLED(10, "MD1 L1MCU protection"),
	REGISTER_BIT_ENABLED(11, "L2SS SMI protection"),
	REGISTER_BIT_ENABLED(12, "L2SS AFF protection"),
	REGISTER_BIT_ENABLED(13, "C2K AXI protection"),
	REGISTER_BIT_ENABLED(14, "AP to C2K protection"),
	REGISTER_BIT_ENABLED(15, "C2K to AP protection"),
	REGISTER_BIT_ENABLED(16, "MD1 L1SYS protection"),
	REGISTER_BIT_ENABLED(18, "CONN to AP protection"),
	REGISTER_BIT_ENABLED(19, "AP to CONN protection"),
	REGISTER_BIT_ENABLED(20, "IOMMU protection"),
	REGISTER_BIT_ENABLED(21, "MFG M0 protection"),
	REGISTER_BIT_ENABLED(23, "MFG Snoop out protection"),
	REGISTER_BIT_ENABLED(31, "ABBMIX protection")
);

DEFINE_REGISTER(INFRA_TOPAXI_PROTECT_STA0, 0x224, "Top AXI Protection Status 0",
	REGISTER_BIT_IDLE(0, "CCI M1 protection"),
	REGISTER_BIT_IDLE(1, "MM M0 protection"),
	REGISTER_BIT_IDLE(2, "MM M1 protection"),
	REGISTER_BIT_IDLE(3, "MD1 PSMCU protection"),
	REGISTER_BIT_IDLE(4, "MD1 MDDMA protection"),
	REGISTER_BIT_IDLE(5, "MD1 MD to AP protection"),
	REGISTER_BIT_IDLE(6, "MMAPB protection"),
	REGISTER_BIT_IDLE(7, "AP to MD MD1 protection"),
	REGISTER_BIT_IDLE(8, "CCI M2 protection"),
	REGISTER_BIT_IDLE(9, "CCI M0 protection"),
	REGISTER_BIT_IDLE(10, "MD1 L1MCU protection"),
	REGISTER_BIT_IDLE(11, "L2SS SMI protection"),
	REGISTER_BIT_IDLE(12, "L2SS AFF protection"),
	REGISTER_BIT_IDLE(13, "C2K AXI protection"),
	REGISTER_BIT_IDLE(14, "AP to C2K protection"),
	REGISTER_BIT_IDLE(15, "C2K to AP protection"),
	REGISTER_BIT_IDLE(16, "MD1 L1SYS protection"),
	REGISTER_BIT_IDLE(18, "CONN to AP protection"),
	REGISTER_BIT_IDLE(19, "AP to CONN protection"),
	REGISTER_BIT_IDLE(20, "IOMMU protection"),
	REGISTER_BIT_IDLE(21, "MFG M0 protection"),
	REGISTER_BIT_IDLE(23, "MFG Snoop out protection")
);

DEFINE_REGISTER(INFRA_TOPAXI_PROTECT_STA1, 0x228, "Top AXI Protection Status 1",
	REGISTER_BIT_READY(0, "CCI M1 protection"),
	REGISTER_BIT_READY(1, "MM M0 protection"),
	REGISTER_BIT_READY(2, "MM M1 protection"),
	REGISTER_BIT_READY(3, "MD1 PSMCU protection"),
	REGISTER_BIT_READY(4, "MD1 MDDMA protection"),
	REGISTER_BIT_READY(5, "MD1 MD to AP protection"),
	REGISTER_BIT_READY(6, "MMAPB protection"),
	REGISTER_BIT_READY(7, "AP to MD MD1 protection"),
	REGISTER_BIT_READY(8, "CCI M2 protection"),
	REGISTER_BIT_READY(9, "CCI M0 protection"),
	REGISTER_BIT_READY(10, "MD1 L1MCU protection"),
	REGISTER_BIT_READY(11, "L2SS SMI protection"),
	REGISTER_BIT_READY(12, "L2SS AFF protection"),
	REGISTER_BIT_READY(13, "C2K AXI protection"),
	REGISTER_BIT_READY(14, "AP to C2K protection"),
	REGISTER_BIT_READY(15, "C2K to AP protection"),
	REGISTER_BIT_READY(16, "MD1 L1SYS protection"),
	REGISTER_BIT_READY(18, "CONN to AP protection"),
	REGISTER_BIT_READY(19, "AP to CONN protection"),
	REGISTER_BIT_READY(20, "IOMMU protection"),
	REGISTER_BIT_READY(21, "MFG M0 protection"),
	REGISTER_BIT_READY(23, "MFG Snoop out protection")
);

void __init mt6797_debug_bus_protect_regs_init(struct dentry *reg_dir)
{
	REGISTER_FILE(reg_dir, INFRACFG_BASE, INFRA_TOPAXI_PROTECT_EN);
	REGISTER_FILE(reg_dir, INFRACFG_BASE, INFRA_TOPAXI_PROTECT_STA0);
	REGISTER_FILE(reg_dir, INFRACFG_BASE, INFRA_TOPAXI_PROTECT_STA1);
}
