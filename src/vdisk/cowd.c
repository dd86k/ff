#include <stdio.h>
#include "../ff.h"
#include "../utils.h"
#include "../settings.h"
#include "cowd.h"

void scan_cowd() {
	struct COWDisk_Header h;
	_ddread(&h, sizeof(h));
	if (h.flags != 3) {
		report_text();
		return;
	}
	long long size = h.numSectors * 512;
	reportn("ESXi COW vdisk v");
	printf("%d, \"%s\", ", h.version, h.name);
	_printfd(size);
	printl("\n");

	if (More) {
		printf(
			"Cylinders: %d\n"
			"Heads: %d\n"
			"Sectors: %d\n",
			h.root.cylinders, h.root.heads, h.root.sectors
		);
	}
}