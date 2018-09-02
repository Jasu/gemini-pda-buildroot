// SPDX-License-Identifier: GPL-2.0

#include <linux/kernel.h>
#include <linux/module.h>
#include "regdump.h"

#define PERICFG_BASE 0x10003000

#define PDN0_BITS(bit_type_) \
	REGISTER_BIT_##bit_type_(0, "DISP PWM"), \
	REGISTER_BIT_##bit_type_(1, "THERM"), \
	REGISTER_BIT_##bit_type_(2, "PWM1"), \
	REGISTER_BIT_##bit_type_(3, "PWM2"), \
	REGISTER_BIT_##bit_type_(4, "PWM3"), \
	REGISTER_BIT_##bit_type_(5, "PWM4"), \
	REGISTER_BIT_##bit_type_(6, "PWM5"), \
	REGISTER_BIT_##bit_type_(7, "PWM6"), \
	REGISTER_BIT_##bit_type_(8, "PWM7"), \
	REGISTER_BIT_##bit_type_(9, "PWM"), \
	REGISTER_BIT_##bit_type_(10, "USB0"), \
	REGISTER_BIT_##bit_type_(11, "IRDA"), \
	REGISTER_BIT_##bit_type_(12, "APDMA"), \
	REGISTER_BIT_##bit_type_(13, "MSDC30_0"), \
	REGISTER_BIT_##bit_type_(14, "MSDC30_1"), \
	REGISTER_BIT_##bit_type_(15, "MSDC30_2 (Maybe? Commented out)"), \
	REGISTER_BIT_##bit_type_(16, "MSDC30_3 (Maybe? Commented out)"), \
	REGISTER_BIT_##bit_type_(17, "UART0"), \
	REGISTER_BIT_##bit_type_(18, "UART1"), \
	REGISTER_BIT_##bit_type_(19, "UART2"), \
	REGISTER_BIT_##bit_type_(20, "UART3"), \
	REGISTER_BIT_##bit_type_(21, "UART4 (Maybe? Commented out)"), \
	REGISTER_BIT_##bit_type_(22, "BTIF"), \
	REGISTER_BIT_##bit_type_(23, "I2C0"), \
	REGISTER_BIT_##bit_type_(24, "I2C1"), \
	REGISTER_BIT_##bit_type_(25, "I2C2"), \
	REGISTER_BIT_##bit_type_(26, "I2C3"), \
	REGISTER_BIT_##bit_type_(27, "AUXADC"), \
	REGISTER_BIT_##bit_type_(28, "SPI0"), \
	REGISTER_BIT_##bit_type_(29, "IRTX")

// Undocumented, see mediatek/base/power/mt6797/mt_clkmgr2.c in the
// Android sources.
DEFINE_REGISTER(PERI_PDN0_STA, 0x018, "Peripheral powerdown status 0",
	PDN0_BITS(OFF));
DEFINE_REGISTER(PERI_PDN0_SET, 0x008, "Peripheral powerdown set 0",
	PDN0_BITS(SET));
DEFINE_REGISTER(PERI_PDN0_CLR, 0x010, "Peripheral powerdown clear 0",
	PDN0_BITS(SET));

void __init mt6797_debug_pericfg_regs_init(struct dentry *regs_dir)
{
	regs_dir = debugfs_create_dir("pericfg", regs_dir);
	REGISTER_FILE(regs_dir, PERICFG_BASE, PERI_PDN0_STA);
	REGISTER_FILE(regs_dir, PERICFG_BASE, PERI_PDN0_SET);
	REGISTER_FILE(regs_dir, PERICFG_BASE, PERI_PDN0_CLR);
}
