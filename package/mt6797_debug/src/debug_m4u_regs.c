// SPDX-License-Identifier: GPL-2.0

#include <linux/kernel.h>
#include <linux/module.h>
#include "regdump.h"

#define M4U_BASE 0x10205000

DEFINE_REGISTER_SIMPLE(M4U_PT_BASE_ADDR, 0x000, "M4U page table PA 1");
DEFINE_REGISTER_SIMPLE(M4U_PT_BASE_ADDR_SEC, 0x004, "M4U page table PA 2");

DEFINE_REGISTER(M4U_CTRL, 0x110, "M4U control",
	 REGISTER_BIT_DISABLED(0, "PFH"),
	 REGISTER_BIT_DISABLED(1, "TLB walk"),
	 REGISTER_BIT_ENABLED(2, "Monitor"),
	 REGISTER_BIT_ON(3, "Monitor clear"),
	 REGISTER_BIT_ON(4, "PFH RT RPL mode"),
	 REGISTER_FIELD(5, 6, "TF protection value"),
	 REGISTER_BIT_ENABLED(7, "INT hang"),
	 REGISTER_BIT_ENABLED(8, "Cohere"),
	 REGISTER_BIT_ENABLED(9, "In-order writes"),
	 REGISTER_BIT_ENABLED(10, "Main TLB shareall")
);

DEFINE_REGISTER(M4U_IVRP_PADDR, 0x114, "M4U trans. fault prot. buf.",
	 REGISTER_FIELD(0, 30, "Address (shifted right by 1)"),
	 REGISTER_BIT_ON(31, "4GB mode")
);

void __init mt6797_debug_m4u_regs_init(struct dentry *reg_dir)
{
	REGISTER_FILE(reg_dir, M4U_BASE, M4U_PT_BASE_ADDR);
	REGISTER_FILE(reg_dir, M4U_BASE, M4U_PT_BASE_ADDR_SEC);
	REGISTER_FILE(reg_dir, M4U_BASE, M4U_CTRL);
	REGISTER_FILE(reg_dir, M4U_BASE, M4U_IVRP_PADDR);
}
