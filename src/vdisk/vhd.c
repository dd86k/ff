#include <stdio.h>
#include "../ff.h"
#include "../utils.h"
#include "../settings.h"
#include "vhd.h"

void scan_vhd() { // big-endian
	struct vhd_hdr h;
	_ddread(&h, sizeof(h));

	h.features = bswap32(h.features);
	if ((h.features & F_RES) == 0) {
		report_text();
		return;
	}

	h.disk_type = bswap32(h.disk_type);

	char *d, *os;

	switch(h.disk_type) {
	case D_FIXED:   d = "fixed"; break;
	case D_DYNAMIC: d = "dynamic"; break;
	case D_DIFF:    d = "differencing"; break;
	default: d = h.disk_type < 7 ? "reserved (deprecated)" : "type?";
	}

	switch (h.creator_os) {
	case OS_WINDOWS: os = "Windows"; break;
	case OS_MAC:     os = "macOS"; break;
	default:         os = "OS?"; break;
	}

	reportf("Microsoft VHD vdisk v%d.%d, %s, %s v%d.%d on %s, ",
		bswap16(h.major), bswap16(h.minor), d,
		h.creator_app, bswap16(h.creator_major), bswap16(h.creator_minor),
		os);

	_printfd(bswap64(h.size_current));
	putchar('/');
	_printfd(bswap64(h.size_original));
	printl(" used");

	if (h.features & F_TEMPORARY)
		printl(", temporary");

	if (h.savedState)
		printl(", saved state");

	putchar('\n');

	if (More) {
		printl("UUID: ");
		print_array(h.uuid, sizeof(h.uuid));
		printf(
			"Cylinders: %d\n"
			"Heads: %d\n"
			"Sectors: %d\n",
			h.cylinders, h.heads, h.sectors
		);
	}
}