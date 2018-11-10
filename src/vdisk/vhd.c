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
	reportf("Microsoft VHD vdisk v%d.%d, ", bswap16(h.major), bswap16(h.minor));
	switch(h.disk_type) {
	case D_FIXED: printl("fixed"); break;
	case D_DYNAMIC: printl("dynamic"); break;
	case D_DIFF: printl("differencing"); break;
	default:
		if (h.disk_type < 7)
			printl("reserved (deprecated)");
		else {
			printl("?");
			return;
		}
	}

	printf(", %s v%d.%d on ",
		h.creator_app, bswap16(h.creator_major), bswap16(h.creator_minor));

	switch (h.creator_os) {
	case OS_WINDOWS: printl("Windows"); break;
	case OS_MAC:     printl("macOS"); break;
	default: printl("OS?"); break;
	}

	printl(", ");
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