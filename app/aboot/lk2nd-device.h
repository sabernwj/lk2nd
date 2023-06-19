/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef __LK2ND_DEVICE_H
#define __LK2ND_DEVICE_H

#include <dev_tree.h>

enum aboot_modes {
	ABOOT_MODE_UNKNOWN = 0,
	ABOOT_MODE_NORMAL,
	ABOOT_MODE_CHARGER,
	ABOOT_MODE_RECOVERY,
};

struct lk2nd_panel {
	const char *name;
	const char *old_compatible;
	const char *compatible;
	int compatible_size;
};

struct lk2nd_device {
	void *fdt;
	const char *model;
	const char *cmdline;

	const char *device;
	const char *bootloader;
	const char *serialno;
	const char *carrier;
	const char *radio;
	const char *slot_suffix;

	const char *wt_board_id;
#ifdef MI8937_KERNEL
	const char *mi8937_bootloader;
	const char *mi8937_device;
#endif

	enum aboot_modes aboot_mode;

	void *pstore;
	unsigned int pstore_size;
	bool dev_mode;

	struct lk2nd_panel panel;
};

extern struct lk2nd_device lk2nd_dev;

void lk2nd_init(void);
int lk2nd_fdt_parse_early_uart(void);

void lk2nd_samsung_muic_reset(const void *fdt, int offset);
void lk2nd_motorola_smem_write_unit_info(const void *fdt, int offset);

void lk2nd_update_device_tree(void *fdt, const char *cmdline);

#endif
