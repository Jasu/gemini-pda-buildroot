// SPDX-License-Identifier: GPL-2.0

#include <linux/arm-smccc.h>
#include <linux/debugfs.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/seq_file.h>

#define MTK_SIP_KERNEL_EMIMPU_READ 0x82000208

static const char * permission_map[] = {
	"not protected",
	"RW for secure only",
	"RW for secure, RO for non-secure",
	"RW for secure, WO for non-secure",
	"RO for both secure and non-secure",
	"forbidden for all",
	"RO for secure, RW for non-secure",
	"undefined",
};

static unsigned long emi_read(unsigned long offset)
{
	struct arm_smccc_res res;
	arm_smccc_smc(MTK_SIP_KERNEL_EMIMPU_READ, offset, 0, 0, 0, 0, 0, 0,
		&res);
	return res.a0;
}

static void debug_emi_mpu_show_region(struct seq_file *seq,
	int region_base, u64 reg_base, int region)
{
	u64 start, end, config_reg;
	u32 val;
	val = emi_read(reg_base + region * 8);
	start = val & 0xFFFF0000;
	end =  ((val & 0xFFFF) << 16) + 0xFFFF;
	seq_printf(seq, "Region %d - 0x%llx-0x%llx",
		region_base + region, start, end);

	config_reg = reg_base + 0x40 + region * 4;
	if (region >= 4) {
		// Config regs are interleaved
		config_reg -= 12;
	}

	val = emi_read(config_reg);
	if ((val & GENMASK(8 * 3, 0)) == 0) {
		seq_printf(seq, " is not protected.\n");
	} else {
		int domain;
		seq_printf(seq, ":\n");
		for (domain = 0; domain < 8; ++domain) {
			u32 domain_config = (val >> (domain * 3)) & 7;
			seq_printf(seq, "\tDomain %d is %s.\n",
				domain, permission_map[domain_config]);
		}
	}

	if (val & BIT(31)) {
		seq_printf(seq,
			"\tRegion is locked (cannot be reconfigured).\n");
	}
}

static int debug_emi_mpu_show_bank(struct seq_file *seq,
	       	int bank, u64 reg_base)
{
	int region;
	seq_printf(seq, "Bank %d\n==================================\n", bank);
	for (region = 0; region < 8; ++region) {
		debug_emi_mpu_show_region(seq, bank * 8,
			bank * 8 + reg_base, region);
	}
	if (bank != 2)
		seq_printf(seq, "\n");
	return 0;
}

static int debug_emi_mpu_show(struct seq_file *seq, void *p) {
	int i;
	for (i = 0; i < 3; ++i) {
		debug_emi_mpu_show_bank(seq, i, 0x160 + i * 0x100);
	}
	return 0;
}

static int emi_mpu_debug_open(struct inode *inode, struct file *file)
{
	return single_open(file, debug_emi_mpu_show, inode->i_private);
}

static const struct file_operations emi_mpu_debug_fops = {
	.owner = THIS_MODULE,
	.open = emi_mpu_debug_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

void __init mt6797_debug_emi_mpu_init(struct dentry *debug_dir)
{
	debugfs_create_file("emi_mpu", S_IFREG | S_IRUGO, debug_dir, NULL,
		       &emi_mpu_debug_fops);
}
