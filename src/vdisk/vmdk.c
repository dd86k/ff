#include <stdio.h>
#include "../ff.h"
#include "../utils.h"
#include "../settings.h"
#include "vmdk.h"

void scan_vmdk() {
	struct SparseExtentHeader h;
	_osread(&h, sizeof(h));

	char *c;

	switch (h.compressAlgorithm) {
	case 0:  c = "no"; break;
	case 1:  c = "DEFLATE"; break;
	default: c = "?"; break;
	}

	reportf("VMware vdisk v%u, %s compression, ", h.version, c);

	_printfd(h.capacity * 512);

	if (h.uncleanShutdown)
		printl(", unclean shutdown");

	putchar('\n');

	if (More) {
		printf(
			"Capacity: %llu Sectors\n"
			"Overhead: %llu Sectors\n"
			"Grain size (Raw): %llu Sectors\n",
			h.capacity, h.overHead, h.grainSize
		);
	}
}