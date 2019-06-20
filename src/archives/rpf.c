#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "rpf.h"
#include <stdio.h>

void scan_rpf(uint32_t s) {
	struct rpf_hdr h;
	_osread(&h, sizeof(h));

	char *g;

	switch (s >>= 24) {
	case 0x30: g = "Table Tennis"; break;
	case 0x32: g = "GTA IV"; break;
	case 0x33: g = "GTA IV:A&MC:LA"; break;
	case 0x34: g = "Max Payne 3"; break;
	case 0x36: g = "Red Dead Redemption"; break;
	case 0x37: g = "GTA V"; break;
	}

	reportf("RPF %sencrypted archive v%u for %s, %u entries\n",
		h.encrypted ? "" : "un", s, g, h.numentries);
}