#include <stdio.h>
#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "cab.h"

void scan_cab() {
	struct cfh_hdr h;
	_ddread(&h, sizeof(h));
	reportf("Microsoft Cabinet archive vu.%u, ", h.major, h.minor);
	_printfd(h.size);
	printf(", %u files, %u folders\n", h.files, h.folders);
}