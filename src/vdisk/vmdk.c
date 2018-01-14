#include <stdio.h>
#include "../ff.h"
#include "../utils.h"
#include "../settings.h"
#include "vmdk.h"

void scan_vmdk() {
	struct SparseExtentHeader h;
	_ddread(&h, sizeof(h));

	reportn("VMware disk v");
	printf("%d, ", h.version);

	//if (h.flags & COMPRESSED)
	switch (h.compressAlgorithm) {
	case 0: printf("no"); break;
	case 1: printf("DEFLATE"); break;
	default: printf("?"); break;
	}
	printf(" compression");

	if (h.uncleanShutdown)
		printf(", unclean shutdown");

	puts("");

	if (More) {
		printf(
			"Capacity: %lld Sectors\n"
			"Overhead: %lld Sectors\n"
			"Grain size (Raw): %lld Sectors\n",
			h.capacity, h.overHead, h.grainSize
		);
	}
}