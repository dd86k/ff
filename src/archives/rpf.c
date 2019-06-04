#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "rpf.h"
#include <stdio.h>

void scan_rpf(uint32_t s) {
	struct rpf_hdr h;
	_ddread(&h, sizeof(h));

	char *e, *g;

	e = h.encrypted ? "encrypted" : "unencrypted";

	switch (s) {
	case 0x30465052: g = "Table Tennis"; break;
	case 0x32465052: g = "GTA IV"; break;
	case 0x33465052: g = "GTA IV:A&MC:LA"; break;
	case 0x34465052: g = "Max Payne 3"; break;
	case 0x36465052: g = "Red Dead Redemption"; break;
	case 0x37465052: g = "GTA V"; break;
	}

	reportf("RPF %s archive v%u for %s, %u entries",
		e, s >> 24, g, h.numentries);
}