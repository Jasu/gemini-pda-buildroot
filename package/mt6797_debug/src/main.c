// SPDX-License-Identifier: GPL-2.0

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/debugfs.h>

void mt6797_debug_bus_protect_regs_init(struct dentry *regs_dir);
void mt6797_debug_gpio_regs_init(struct dentry *regs_dir);
void mt6797_debug_gpuldo_regs_init(struct dentry *regs_dir);
void mt6797_debug_emi_mpu_init(struct dentry *debug_dir);
void mt6797_debug_emi_regs_init(struct dentry *regs_dir);
void mt6797_debug_io_cfg_l_regs_init(struct dentry *regs_dir);
void mt6797_debug_m4u_regs_init(struct dentry *regs_dir);
void mt6797_debug_pericfg_regs_init(struct dentry *regs_dir);
void mt6797_debug_pll_init(struct dentry *debug_dir);
void mt6797_debug_psci_init(struct dentry *debug_dir);
void mt6797_debug_spm_regs_init(struct dentry *debug_dir);
void mt6797_debug_uart_regs_init(struct dentry *regs_dir);
void mt6797_debug_usb_sifslv_u2phy_init(struct dentry *regs_dir);

static struct dentry *debug_dir;

static int __init mt6797_debug_init(void)
{
	debug_dir = debugfs_create_dir("mt6797", NULL);
	struct dentry * regs_dir = debugfs_create_dir("regs", debug_dir);

	mt6797_debug_bus_protect_regs_init(regs_dir);
	mt6797_debug_gpio_regs_init(regs_dir);
	mt6797_debug_gpuldo_regs_init(regs_dir);
	mt6797_debug_emi_mpu_init(debug_dir);
	mt6797_debug_emi_regs_init(regs_dir);
	mt6797_debug_io_cfg_l_regs_init(regs_dir);
	mt6797_debug_m4u_regs_init(regs_dir);
	mt6797_debug_pericfg_regs_init(regs_dir);
	mt6797_debug_pll_init(debug_dir);
	mt6797_debug_psci_init(debug_dir);
	mt6797_debug_spm_regs_init(regs_dir);
	mt6797_debug_uart_regs_init(regs_dir);
	mt6797_debug_usb_sifslv_u2phy_init(regs_dir);

	return 0;
}

static void __exit mt6797_debug_exit(void)
{
	debugfs_remove_recursive(debug_dir);
}

module_init(mt6797_debug_init);
module_exit(mt6797_debug_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jasper Mattsson <jasu@njomotys.info>");
MODULE_DESCRIPTION("MediaTek MT6797 debug functionality");
