#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "rpf.h"
#include <stdio.h>

void scan_rpf(unsigned int s) {
	struct rpf_hdr h;
	_ddread(&h, sizeof(h));
	reportn("RPF ");
	if (h.encrypted) printf("encrypted ");
	printf("archive v%c (", (s >> 24) + 0x30);
	switch (s) {
	case 0x30465052: printf("Table Tennis"); break;
	case 0x32465052: printf("GTA IV"); break;
	case 0x33465052: printf("GTA IV:A&MC:LA"); break;
	case 0x34465052: printf("Max Payne 3"); break;
	case 0x36465052: printf("Red Dead Redemption"); break;
	case 0x37465052: printf("GTA V"); break;
	}
	printf("), %d entries\n", h.numentries);
}