#include <stdio.h>
#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "7zip.h"
#include <inttypes.h>

void scan_7zip() {
	struct _7zip_h h;
	_ddread(&h, sizeof(struct _7zip_h));

	reportf("7-Zip archive (7z) v%u.%u, crc %08X\n",
		h.vmajor, h.vminor, h.ncrc);

	if (More) {
		printf(
			"Next header offset: %"PRIX64"h\n"
			"Next header size: %"PRId64"\n"
			"Next header crc: %08X\n",
			h.nhoffset, h.nhsize, h.nhcrc
		);
	}
}