// SPDX-License-Identifier: GPL-2.0

#include <linux/kernel.h>
#include <linux/module.h>
#include "regdump.h"

#define EMI_CON_BASE 0x10203000

DEFINE_REGISTER(EMI_CONM, 0x060, "EMI Misc. configuration",
	 REGISTER_BIT_DISABLED(24, "Write cmd and data DCM"),
	 REGISTER_BIT_DISABLED(25, "Read cmd DCM"),
	 REGISTER_BIT_DISABLED(26, "Read data DCM"),
	 REGISTER_BIT_DISABLED(27, "Reserved"),
	 REGISTER_BIT_DISABLED(28, "emi_check module DCM"),
	 REGISTER_BIT_DISABLED(29, "emi_command arbiter DCM"),
	 REGISTER_BIT_DISABLED(30, "EMI top DCM"),
	 REGISTER_BIT_DISABLED(31, "EMI APB DCM"),
	 REGISTER_FIELD(20, 23, "Res. write buffer M0 ultra/under BW limiter req"),
	 REGISTER_FIELD(16, 19, "Res. read buffer M0 ultra/under BW limiter req"),
	 REGISTER_BIT_ENABLED(10, "EMI/DRAMC access"),
	 REGISTER_ENUM(8, 9, "Age decrement speed when BW > allocated",
			     "No decrement",
			     "1/4 speed decrement",
			     "Normal speed decrement",
			     "1/2 speed decrement"),
	 REGISTER_BIT(7, "M7 prio: receive page hit command first",
		"M7 prio: do not receive page hit command first"),
	 REGISTER_BIT(7, "M7 prio: receive page hit command first",
		      "M7 prio: do not receive page hit command first"),
	 REGISTER_BIT(6, "M6 prio: receive page hit command first",
		      "M6 prio: do not receive page hit command first"),
	 REGISTER_BIT(5, "M5 prio: receive page hit command first",
		      "M5 prio: do not receive page hit command first"),
	 REGISTER_BIT(4, "M4 prio: receive page hit command first",
		      "M4 prio: do not receive page hit command first"),
	 REGISTER_BIT(3, "M3 prio: receive page hit command first",
		      "M3 prio: do not receive page hit command first"),
	 REGISTER_BIT(2, "M2 prio: receive page hit command first",
		      "M2 prio: do not receive page hit command first"),
	 REGISTER_BIT(1, "M1 prio: receive page hit command first",
		      "M1 prio: do not receive page hit command first"),
	 REGISTER_BIT(0, "M0 prio: receive page hit command first",
		      "M0 prio: do not receive page hit command first")

);

void __init mt6797_debug_emi_regs_init(struct dentry *regs_dir)
{
	regs_dir = debugfs_create_dir("emi", regs_dir);

	REGISTER_FILE(regs_dir, EMI_CON_BASE, EMI_CONM);
}
