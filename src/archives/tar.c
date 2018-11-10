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

	reportn("Tar archive, ");

	switch (h.linkflag) {
	case 0:
	case '0': printl("normal, "); break;
	case '1': printl("link, "); break;
	case '2': printl("syslink, "); break;
	case '3': printl("character special, "); break;
	case '4': printl("block special, "); break;
	case '5': printl("directory, "); break;
	case '6': printl("FIFO, "); break;
	case '7': printl("contiguous, "); break;
	default: puts("unknown"); return;
	}

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