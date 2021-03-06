#include <stdio.h>
#include "../ff.h"
#include "../utils.h"
#include "../settings.h"
#include "cowd.h"

void scan_cowd() {
	struct COWDisk_Header h;
	_osread(&h, sizeof(h));

	if (h.flags != 3) {
		report_text();
		return;
	}

	long long size = h.numSectors * 512;

	reportf("ESXi COW vdisk v%u, \"%.60s\", ", h.version, h.name);
	_printfd(size);
	putchar('\n');

	if (More) {
		printf(
			"Cylinders: %u\n"
			"Heads: %u\n"
			"Sectors: %u\n",
			h.root.cylinders, h.root.heads, h.root.sectors
		);
	}
}