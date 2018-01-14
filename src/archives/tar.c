#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "tar.h"
#include <stdio.h>

void scan_tar() {
	struct tar_hdr h;
	_ddseek(0, SEEK_SET);
	_ddread(&h, sizeof(h));

	switch (h.linkflag) {
		case 0:
		case '0': reportn("Normal"); break;
		case '1': reportn("Link"); break;
		case '2': reportn("Syslink"); break;
		case '3': reportn("Character special"); break;
		case '4': reportn("Block special"); break;
		case '5': reportn("Directory"); break;
		case '6': reportn("FIFO special"); break;
		case '7': reportn("Contiguous"); break;
		default: puts(""); return;
	}

	printf(" Tar archive of %s bytes\n", h.size);

	if (More) {
		printf(
			"Name: %s\n"
			"Link name: %s\n"
			"uname: %s\n"
			"gname: %s\n"
			"Magic: %s\n"
			"Mode: %s\n"
			"Checksum: %s\n"
			"Major version: %s\n"
			"Major version: %s\n",
			h.name, h.linkname, h.uname,
			h.gname, h.magic, h.mode,
			h.chksum, h.devmajor, h.devminor
		);
	}
}