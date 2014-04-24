

#include "check.h"
#include "karma.h"

int karma_partition(struct parsed_partitions *state)
{
	int i;
	int slot = 1;
	Sector sect;
	unsigned char *data;
	struct disklabel {
		u8 d_reserved[270];
		struct d_partition {
			__le32 p_res;
			u8 p_fstype;
			u8 p_res2[3];
			__le32 p_offset;
			__le32 p_size;
		} d_partitions[2];
		u8 d_blank[208];
		__le16 d_magic;
	} __attribute__((packed)) *label;
	struct d_partition *p;

	data = read_part_sector(state, 0, &sect);
	if (!data)
		return -1;

	label = (struct disklabel *)data;
	if (le16_to_cpu(label->d_magic) != KARMA_LABEL_MAGIC) {
		put_dev_sector(sect);
		return 0;
	}

	p = label->d_partitions;
	for (i = 0 ; i < 2; i++, p++) {
		if (slot == state->limit)
			break;

		if (p->p_fstype == 0x4d && le32_to_cpu(p->p_size)) {
			put_partition(state, slot, le32_to_cpu(p->p_offset),
				le32_to_cpu(p->p_size));
		}
		slot++;
	}
	printk("\n");
	put_dev_sector(sect);
	return 1;
}
