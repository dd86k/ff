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
		puts("VirtualBox VDI vdisk, unsupported major version");
		return;
	}
	reportf("VirtualBox VDI vdisk v%d.%d, ", h.majorv, h.minorv);
	switch (sh.u32Type) {
	case 1: printl("dynamic"); break;
	case 2: printl("static"); break;
	default: printl("type?"); break;
	}
	printl(", ");
	_printfd(sh.cbDisk);
	putchar('\n');

	if (More) {
		printl("Create UUID:");
		print_array(sh.uuidCreate, 16);
		printl("Modify UUID:");
		print_array(sh.uuidModify, 16);
		printl("Link UUID  :");
		print_array(sh.uuidLinkage, 16);
		if (h.majorv >= 1) {
			printl("ParentModify UUID:");
			print_array(sh.uuidParentModify, 16);
		}
		printf(
			"Cylinders (Legacy): %d\n"
			"Heads (Legacy): %d\n"
			"Sectors (Legacy): %d\n"
			"Sector size (Legacy): %d\n"
			"Header size: %d\n",
			sh.LegacyGeometry.cCylinders,
			sh.LegacyGeometry.cHeads,
			sh.LegacyGeometry.cSectors,
			sh.LegacyGeometry.cbSector,
			sh.cbHeader
		);
	}
}