#include <stdio.h>
#include "../ff.h"
#include "../utils.h"
#include "snes.h"

void scan_kspc() {
	struct spc2_hdr h;
	_ddread(&h, sizeof(h));

	reportf("SNES sound (SPC2) v%u.%u, %u entries\n",
		h.major, h.minor, h.entries);
}