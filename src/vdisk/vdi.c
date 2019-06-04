#include <stdio.h>
#include <string.h>
#include "../ff.h"
#include "../utils.h"
#include "../settings.h"
#include "vdi.h"

void scan_vdi() {
	_ddseek(64, SEEK_SET); // Skip description, char[64]
	struct vdi_hdr h;
	_ddread(&h, sizeof(h));

	if (h.magic != VDIMAGIC) {
		report_text(); // Coincidence
		return;
	}

	struct VDIHEADER1 sh;

	switch (h.majorv) { // Use latest major version natively
	case 1:
		_ddread(&sh, sizeof(sh));
		break;
	case 0: { // Or else, translate
		struct VDIHEADER0 vd0;
		_ddread(&vd0, sizeof(vd0));
		sh.cbDisk = vd0.cbDisk;
		sh.u32Type = vd0.u32Type;
		memcpy(&sh.uuidCreate, &vd0.uuidCreate, 16);
		memcpy(&sh.uuidModify, &vd0.uuidModify, 16);
		memcpy(&sh.uuidLinkage, &vd0.uuidLinkage, 16);
		memcpy(&sh.LegacyGeometry, &vd0.LegacyGeometry, sizeof(vd0.LegacyGeometry));
		break;
	}
	default:
		report("VirtualBox VDI vdisk?");
		return;
	}

	char *t;

	switch (sh.u32Type) {
	case 1:  t = "dynamic"; break;
	case 2:  t = "static"; break;
	default: t = "type?"; break;
	}

	reportf("VirtualBox VDI vdisk v%u.%u, %s, ", h.majorv, h.minorv, t);
	_printfd(sh.cbDisk);
	putchar('\n');

	if (More) {
		print_a("Create UUID :", sh.uuidCreate, 16);
		print_a("Modify UUID :", sh.uuidModify, 16);
		print_a("Link UUID   :", sh.uuidLinkage, 16);
		if (h.majorv >= 1)
			print_a("Parent UUID :", sh.uuidParentModify, 16);
		printf(
			"Cylinders (Legacy)  : %u\n"
			"Heads (Legacy)      : %u\n"
			"Sectors (Legacy)    : %u\n"
			"Sector size (Legacy): %u\n"
			"Header size         : %u\n",
			sh.LegacyGeometry.cCylinders,
			sh.LegacyGeometry.cHeads,
			sh.LegacyGeometry.cSectors,
			sh.LegacyGeometry.cbSector,
			sh.cbHeader
		);
	}
}