// SPDX-License-Identifier: GPL-2.0

#include <asm/cputype.h>
#include <linux/arm-smccc.h>
#include <linux/debugfs.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/seq_file.h>
#include <uapi/linux/psci.h>

static const char * affinities[] = { "on", "off", "pending on" };

static int debug_psci_show(struct seq_file *seq, void *p)
{
	unsigned int cpu;
	struct arm_smccc_res res;
	/* Reading affinity of CPU 0 hangs the system for some reason. */
	seq_printf(seq, "Current CPU MPIDR affinity is %llx.\n",
		read_cpuid_mpidr() & MPIDR_HWID_BITMASK);
	seq_printf(seq, "CPU 0 (hwid=0) omitted.\n");
	for (cpu = 1; cpu < 10; ++cpu) {
		u64 hwid;

		if (cpu < 4) {
			hwid = cpu;
		} else if (cpu < 8) {
			hwid = cpu - 4 + 0x100;
		} else if (cpu < 10) {
			hwid = cpu - 8 + 0x200;
		} else {
			seq_printf(seq, "Error: CPU %d is not supported.\n",
				cpu);
			continue;
		}

		arm_smccc_smc(PSCI_0_2_FN64_AFFINITY_INFO, hwid, 0, 0, 0,
			0, 0, 0, &res);
		seq_printf(seq, "CPU %d (hwid=0x%llx) ", cpu, hwid);
		if (res.a0 < 3)
			seq_printf(seq, "is %s.\n", affinities[res.a0]);
		else
			seq_printf(seq, "has an unknown affinity of %lx.\n",
				res.a0);
	}
	return 0;
}

DEFINE_SHOW_ATTRIBUTE(debug_psci);

void __init mt6797_debug_psci_init(struct dentry *debug_dir)
{
	debugfs_create_file("psci_status", S_IFREG | S_IRUGO, debug_dir, NULL,
		       &debug_psci_fops);
}
