// SPDX-License-Identifier: GPL-2.0

#include <linux/debugfs.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/seq_file.h>

#define TOPCKGEN_BASE		0x10000000
#define TOPCKGEN_LENGTH		0x1000
// Offsets relative to topckgen
#define CLK_DBG_CFG             0x10C
#define CLK_MISC_CFG_0          0x104
#define CLK26CALI_0             0x220
#define CLK26CALI_1             0x224

static int debug_pll_show(struct seq_file *seq, void *p)
{
	unsigned int original_cali_0, original_cali_1, original_dbg_cfg,
	       	original_misc_cfg_0, readout, i;
	static __iomem void *topckgen_base;

	topckgen_base = ioremap_nocache(TOPCKGEN_BASE, TOPCKGEN_LENGTH);

	// Note: we are not doing mutual exclusion with clk/mediatek. This
	// might blow up the device.

	// Copy original register values
	original_cali_0 = readl(topckgen_base + CLK26CALI_0);
	original_cali_1 = readl(topckgen_base + CLK26CALI_1);
	original_dbg_cfg = readl(topckgen_base + CLK_DBG_CFG);

	writel(BIT(8) | BIT(0), topckgen_base + CLK_DBG_CFG);

	// Clear the clock meter divider setting
	// !!!!! Race condition here, since CLK_MISC_CFG_0 is also used by
	// clk/mediatek.
	original_misc_cfg_0 = readl(topckgen_base + CLK_MISC_CFG_0);
	writel(original_misc_cfg_0 & 0x00FFFFFF, topckgen_base + CLK_MISC_CFG_0);


	writel(0x1000, topckgen_base + CLK26CALI_0);
	udelay(50);
	writel(0x1010, topckgen_base + CLK26CALI_0);

	/* Note that the loop below may block the kernel for up to 100ms. */
	for (i = 0; i < 10; ++i) {
		mdelay(10);
		readout = readl(topckgen_base + CLK26CALI_0);
		if (!(readout & 0x10)) {
			break;
		}
	}

	writel(original_misc_cfg_0, topckgen_base + CLK_MISC_CFG_0);
	writel(original_dbg_cfg, topckgen_base + CLK_DBG_CFG);
	writel(original_cali_0, topckgen_base + CLK26CALI_0);

	if (readout & 0x10) {
		seq_printf(seq, "Did not get a readout from CLK26CALI_0.\n");
		return 0;
	}

	readout = readl(topckgen_base + CLK26CALI_1);
	writel(original_cali_1, topckgen_base + CLK26CALI_1);

	readout &= 0xFFFF;
	readout *= 26000;
	readout /= 1024;

	seq_printf(seq, "Main clock (bus) running at %d kHz.\n", readout);
	iounmap(topckgen_base);
	return 0;
}

DEFINE_SHOW_ATTRIBUTE(debug_pll);

void __init mt6797_debug_pll_init(struct dentry *debug_dir)
{
	debugfs_create_file("pll_bus", S_IFREG | S_IRUGO, debug_dir, NULL,
		       &debug_pll_fops);
}
