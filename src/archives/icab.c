#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "icab.h"
#include <stdio.h>

void scan_icab() {
	struct iscab_hdr h;
	_ddread(&h, sizeof(h));
	char *r;
	switch (h.version) {
	case LEGACY:    r = "(Legacy)";  break;
	case v2_20_905: r = "v2.20.905"; break;
	case v3_00_065: r = "v3.00.065"; break;
	case v5_00_000: r = "v5.00.000"; break;
	default: r = "other"; break;
	}
	reportf("InstallShield CAB archive %s (%Xh) at %Xh (%dB)\n",
		r, h.version, h.desc_offset, h.desc_size);
}