#include <stdio.h>
#include "../ff.h"
#include "../utils.h"
#include "idx.h"

void scan_idx() { // Big Endian
	struct idx_header h;
	_osread(&h, sizeof(h));

	reportf("git Pack Index file v%u, %u objects\n",
		bswap32(h.version), bswap32(h.objn));
}