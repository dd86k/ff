#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "icab.h"
#include <stdio.h>

void scan_icab() {
	struct iscab_hdr h;
	_ddread(&h, sizeof(h));
	reportn("InstallShield CAB archive");
	switch (h.version) {
	case LEGACY:    printl(" (Legacy)");  break;
	case v2_20_905: printl(" v2.20.905"); break;
	case v3_00_065: printl(" v3.00.065"); break;
	case v5_00_000: printl(" v5.00.000"); break;
	default: printf(" (%08Xh)", h.version); break;
	}
	printf(" at %Xh\n", h.desc_offset);
}