#include <stdio.h>
#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "gzip.h"

// http://www.zlib.org/rfc-gzip.html

void scan_gzip() { // big endian
	struct hdr_gzip h;

	_osseek(0, SEEK_SET);
	_osread(&h, sizeof(h));

	char *cm, *bin, *os;

	cm  = h.cm == 8 ? "deflate" : "unknown";
	bin = h.flg & FTEXT ? "text" : "binary";
	switch (h.os) {
	case 0: os = "FAT"; break;
	case 1: os = "Amiga"; break;
	case 2: os = "VMS"; break;
	case 3: os = "Unix"; break;
	case 4: os = "VM/CMS"; break;
	case 5: os = "Atari TOS"; break;
	case 6: os = "HPFS"; break;
	case 7: os = "Macintosh"; break;
	case 8: os = "zSystem"; break;
	case 9: os = "CP/M"; break;
	case 10: os = "TOPS-20"; break;
	case 11: os = "NTFS"; break;
	case 12: os = "QDOS"; break;
	case 13: os = "Acorn RISCOS"; break;
	default: os = "unknown";
	}

	reportf("GZIP (gz) archive, %s, %s, %s filesystem", cm, bin, os);

	if (h.flg & FHCRC)
		puts(", crc16");
	else
		putchar('\n');
}