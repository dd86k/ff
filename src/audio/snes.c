#include <stdio.h>
#include "../ff.h"
#include "../utils.h"
#include "snes.h"

void scan_kspc() {
	struct spc2_hdr h;
	_ddread(&h, sizeof(h));

	reportn("SNES sound (SPC2) v");
	printf("%d.%d, %d of SPC entries\n", h.major, h.minor, h.entries);
}