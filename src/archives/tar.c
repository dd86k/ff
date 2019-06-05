#include <stdio.h>
#include <stdlib.h>
#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "tar.h"

// https://www.gnu.org/software/tar/manual/html_node/Standard.html

void scan_tar() {
	struct tar_hdr h;
	_osseek(0, SEEK_SET);
	_osread(&h, sizeof(h));

	char *l;

	switch (h.typeflag) {
	case 0: case '0': l = "Normal"; break;
	case '1': l = "Link"; break;
	case '2': l = "Syslink"; break;
	case '3': l = "Character special"; break;
	case '4': l = "Block special"; break;
	case '5': l = "Directory"; break;
	case '6': l = "FIFO"; break;
	case '7': l = "Contiguous"; break;
	case 'x': l = "Extended Header"; break;
	case 'g': l = "Global Extended Header"; break;
	default: report("Tar archive?"); return;
	}

	long s = strtol(h.size, NULL, sizeof(h.size));

	reportf("Tar %s archive, \"%.100s\", ", l, h.name);
	_printfd(s);
	putchar('\n');

	if (More) {
		printf(
			"Link name: %.100s\n"
			"uname: %.32s\n"
			"gname: %.32s\n"
			"Magic: %.8s\n"
			"Mode: %.8s\n"
			"Checksum: %.8s\n"
			"Version: %.8s.%.8s\n",
			h.linkname, h.uname,
			h.gname, h.magic, h.mode,
			h.chksum, h.devmajor, h.devminor
		);
	}
}