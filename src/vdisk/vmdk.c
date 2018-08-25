#include <stdio.h>
#include "../ff.h"
#include "../utils.h"
#include "../settings.h"
#include "vmdk.h"

void scan_vmdk() {
	struct SparseExtentHeader h;
	_ddread(&h, sizeof(h));

	reportn("VMware vdisk v");
	printf("%d, ", h.version);

	//if (h.flags & COMPRESSED)
	switch (h.compressAlgorithm) {
	case 0: printl("no"); break;
	case 1: printl("DEFLATE"); break;
	default: printl("?"); break;
	}
	printl(" compression, ");

	_printfd(h.capacity * 512);

	if (h.uncleanShutdown)
		printl(", unclean shutdown");

	putchar('\n');

	if (More) {
		printf(
			"Capacity: %lld Sectors\n"
			"Overhead: %lld Sectors\n"
			"Grain size (Raw): %lld Sectors\n",
			h.capacity, h.overHead, h.grainSize
		);
	}
}