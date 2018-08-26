/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MT6797_DEBUG_REGDUMP_H
#define _MT6797_DEBUG_REGDUMP_H

#include <linux/debugfs.h>
#include <linux/seq_file.h>
#include <linux/types.h>

#define REGISTER_FIELD_SENTINEL	0
#define REGISTER_FIELD_BIT	1
#define REGISTER_FIELD_FIELD	2
#define REGISTER_FIELD_ENUM	3

struct register_field {
	unsigned int type;
	unsigned int mask;
	unsigned int shift;
	const char * desc_enabled;
	const char * desc_disabled;
	const char * desc_enum[32];
};

struct register_definition {
	const char * name;
	const char * desc;
	u64 offset;
	struct register_field fields[];
};

#define REGISTER_BIT_ENABLED(INDEX, NAME) \
	REGISTER_BIT(INDEX, NAME" enabled", NAME" disabled")

#define REGISTER_BIT_DISABLED(INDEX, NAME) \
	REGISTER_BIT(INDEX, NAME" disabled", NAME" enabled")

#define REGISTER_BIT_ON(INDEX, NAME) \
	REGISTER_BIT(INDEX, NAME" on", NAME" off")

#define REGISTER_BIT_OFF(INDEX, NAME) \
	REGISTER_BIT(INDEX, NAME" off", NAME" on")

#define REGISTER_BIT(_index, _desc_enabled, _desc_disabled) {		\
		.type = REGISTER_FIELD_BIT,				\
		.mask = BIT(_index),					\
		.shift = _index,					\
		.desc_enabled = _desc_enabled,				\
		.desc_disabled = _desc_disabled,			\
	}

#define REGISTER_FIELD(_start, _end, _desc) {				\
		.type = REGISTER_FIELD_FIELD,				\
		.mask = GENMASK(_end, _start),				\
		.shift = _start,					\
		.desc_enabled = _desc,					\
		.desc_disabled = _desc,					\
	}

#define REGISTER_ENUM(_start, _end, _desc, ...) {			\
		.type = REGISTER_FIELD_ENUM,				\
		.mask = GENMASK(_end, _start),				\
		.shift = _start,					\
		.desc_enabled = _desc,					\
		.desc_disabled = _desc,					\
		.desc_enum = { __VA_ARGS__ },				\
	}

#define DEFINE_REGISTER(_name, _offset, _desc, ...)			\
	static const struct register_definition register_ ## _name = {	\
		.name = #_name,						\
		.desc = _desc,						\
		.offset = _offset,					\
		.fields = {						\
			__VA_ARGS__,					\
			{ .type = REGISTER_FIELD_SENTINEL },		\
		}							\
	};								\
	static int _name##_show(struct seq_file *seq, void *p)		\
	{								\
		print_register(seq, seq->private, &register_##_name);	\
		return 0;						\
	}								\
	DEFINE_SHOW_ATTRIBUTE(_name)

#define DEFINE_REGISTER_SIMPLE(_name, _offset, _desc)			\
	DEFINE_REGISTER(_name, _offset, _desc,				\
		       	{ .type = REGISTER_FIELD_SENTINEL })

#define REGISTER_FILE(_root, _base, _reg)				\
	debugfs_create_file(#_reg, S_IFREG | S_IRUGO, _root,		\
		       	(void*)_base, &_reg##_fops)

void print_register(struct seq_file *seq, void * base,
	const struct register_definition * def);


#endif
