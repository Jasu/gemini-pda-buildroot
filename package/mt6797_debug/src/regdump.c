// SPDX-License-Identifier: GPL-2.0

#define pr_fmt(fmt) "mt6797_debug: reg: "fmt

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/io.h>
#include "regdump.h"

static void print_field(struct seq_file *seq, u32 val,
	const struct register_field * field)
{
	u32 last_bit = field->shift + field->width - 1;
	u32 mask = GENMASK(field->width + field->shift - 1, field->shift);
	u32 field_value = (val & mask) >> field->shift;

	if (field->type == REGISTER_FIELD_BIT)
		seq_printf(seq, "   %2d: ", field->shift, last_bit);
	else
		seq_printf(seq, "%2d:%2d: ", field->shift, last_bit);

	switch (field->type) {
	case REGISTER_FIELD_BIT:
		seq_printf(seq, "%s\n",
			field_value ? field->desc_enabled : field->desc_disabled);
		break;
	case REGISTER_FIELD_FIELD:
		seq_printf(seq, "%s: %x\n", field->desc_enabled, field_value);
		break;
	case REGISTER_FIELD_ENUM:
		seq_printf(seq, "%s\n", field->desc_enum[field_value]);
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

	seq_printf(seq, "%s@%llx - %s: 0x%x\n",
		def->name, (u64)base, def->desc, val);

	print_bits(seq, val);

	for (field = &def->fields[0]; field->type; ++field) {
		print_field(seq, val, field);
	}

	iounmap(base_mapped);					\
}
