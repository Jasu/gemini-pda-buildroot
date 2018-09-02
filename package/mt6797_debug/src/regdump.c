// SPDX-License-Identifier: GPL-2.0

#define pr_fmt(fmt) "mt6797_debug: reg: "fmt

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/io.h>
#include "regdump.h"

static void print_field(struct seq_file *seq, u32 val,
	const struct register_field * field)
{
	u32 i;
	u32 last_bit = (field->shift % 32) + field->width - 1;
	u32 mask = GENMASK(field->width + (field->shift % 32) - 1, field->shift % 32);
	u32 field_value = (val & mask) >> (field->shift % 32);

	if (field->type == REGISTER_FIELD_BIT)
		seq_printf(seq, "   %02d: ", (field->shift % 32), last_bit);
	else
		seq_printf(seq, "%02d:%02d: ", (field->shift % 32), last_bit);

	switch (field->type) {
	case REGISTER_FIELD_BIT:
		seq_printf(seq, "%s\n",
			field_value ? field->desc_enabled : field->desc_disabled);
		break;
	case REGISTER_FIELD_FIELD:
		seq_printf(seq, "%s: %x\n", field->desc_enabled, field_value);
		break;
	case REGISTER_FIELD_ENUM:
		/* Allow omitting trailing undefined values. */
		for (i = 0; i <= field_value; ++i) {
			if (field->desc_enum[i] == 0) {
				seq_printf(seq, "Undefined (0x%x)\n", field_value);
				return;
			}
		}
		seq_printf(seq, "%s (%d)\n",
			field->desc_enum[field_value], field_value);
		break;
	default:
		seq_printf(seq, "Unknown field type: %d\n", field->type);
		break;
	}

}
static void print_bits(struct seq_file *seq, u32 val)
{
	int i;
	seq_printf(seq, "Bits: 31....24 23....16 15.....8 7......0\n      ");
	for (i = 0; i < 32; ++i) {
		if (i && i % 8 == 0)
			seq_printf(seq, " ");
		seq_printf(seq, (BIT(31 - i) & val) ? "1" : "0");
	}
	seq_printf(seq, "\n\n");
}

void print_register(struct seq_file *seq, void * base,
	const struct register_definition * def)
{
	const __iomem void * base_mapped;
	u32 val;
	const struct register_field * field;

	base_mapped = ioremap_nocache((phys_addr_t)base, PAGE_SIZE);
	val = readl(base_mapped + def->offset);

	seq_printf(seq, "%s@%llx - %s: 0x%08x\n",
		def->name, (u64)base + def->offset, def->desc, val);

	print_bits(seq, val);

	for (field = &def->fields[0]; field->type; ++field) {
		print_field(seq, val, field);
	}

	iounmap(base_mapped);					\
}
