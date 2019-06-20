#include <stdio.h>
#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "xz.h"

// https://tukaani.org/xz/xz-file-format.txt

void scan_xz() {
	struct xz_hdr h;
	_osread(&h, sizeof(h));

	char *f;
	switch (h.flg2 & 0xF) {
	case 0: f = "no"; break;
	case 1: f = "crc32"; break;
	case 4: f = "crc64"; break;
	case 10: f = "sha-256"; break;
	default: f = "reserved";
	}

	reportf("xz archive, %s checksum, header crc32:%08X\n", f, h.crc32);
}