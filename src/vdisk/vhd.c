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
	reportn("Microsoft VHD disk v");
	printf("%d.%d, ", bswap16(h.major), bswap16(h.minor));
	switch(h.disk_type) {
	case D_FIXED: printf("fixed"); break;
	case D_DYNAMIC: printf("dynamic"); break;
	case D_DIFF: printf("differencing"); break;
	default:
		if (h.disk_type < 7)
			printf("reserved (deprecated)");
		else {
			printf("Invalid type");
			return;
		}
	}

	printf(", %s v%d.%d on ",
		h.creator_app, bswap16(h.creator_major), bswap16(h.creator_minor));

	switch (h.creator_os) {
	case OS_WINDOWS: printf("Windows"); break;
	case OS_MAC:     printf("macOS"); break;
	default: printf("OS?"); break;
	}

	printf(", "); _printfd(bswap64(h.size_current));
	printf("/"); _printfd(bswap64(h.size_original));
	printf(" used");

	if (h.features & F_TEMPORARY)
		printf(", temporary");

	if (h.savedState)
		printf(", saved state");

	puts("");

	if (More) {
		printf("UUID: ");
		print_array(h.uuid, sizeof(h.uuid));
		printf(
			"Cylinders: %d\n"
			"Heads: %d\n"
			"Sectors: %d\n",
			h.cylinders, h.heads, h.sectors
		);
	}
}