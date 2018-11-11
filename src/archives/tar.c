#include <stdio.h>
#include <stdlib.h>
#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "tar.h"

void scan_tar() {
	struct tar_hdr h;
	_ddseek(0, SEEK_SET);
	_ddread(&h, sizeof(h));

	long s = strtol(h.size, NULL, sizeof(h.size));

	char *l;

	switch (h.linkflag) {
	case 0:
	case '0': l = "normal"; break;
	case '1': l = "link"; break;
	case '2': l = "syslink"; break;
	case '3': l = "character special"; break;
	case '4': l = "block special"; break;
	case '5': l = "directory"; break;
	case '6': l = "FIFO"; break;
	case '7': l = "contiguous"; break;
	default: report("Tar archive?"); return;
	}

	reportf("Tar archive, %s, ", l);

	_printfd(s);
	putchar('\n');

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