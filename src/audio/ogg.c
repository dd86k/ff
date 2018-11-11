#include <stdio.h>
#include "../ff.h"
#include "../utils.h"
#include "../settings.h"
#include "ogg.h"

void scan_ogg() {
	struct ogg_hdr h;
	_ddread(&h, sizeof(h));
	reportf("Ogg audio v%d with %d segments\n", h.version, h.pages);
	if (More) {
		printf("CRC32: %08X\n", h.crc32);
	}
}