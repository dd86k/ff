#include <stdio.h>
#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "cab.h"

void scan_cab() {
	struct cfh_hdr h;
	_ddread(&h, sizeof(h));
	reportn("Microsoft Cabinet archive v");
	printf("%d.%d, ", h.major, h.minor);
	_printfd(h.size);
	printf(", %d files, %d folders\n", h.files, h.folders);
}