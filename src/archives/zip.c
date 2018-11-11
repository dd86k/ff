#include <stdio.h>
#include <stdlib.h>
#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "zip.h"

void scan_zip() {
	struct pkzip_hdr h;
	_ddread(&h, sizeof(h));

	char *c, *fn;

	switch (h.compression) {
	case 0: c = "Uncompressed"; break;
	case 1: c = "Shrunk"; break;
	case 2: case 3: case 4: case 5:
		c = "Reduced"; break;
	case 6: c = "Imploded"; break;
	case 8: c = "Deflated"; break;
	case 9: c = "Enhanced Deflated"; break;
	case 10: c = "DCL Imploded"; break;
	case 12: c = "BZIP2"; break;
	case 14: c = "LZMA"; break;
	case 18: c = "IBM TERSE"; break;
	case 19: c = "IBM LZ77 z"; break;
	case 98: c = "PPMd Version I, Rev 1"; break;
	default: c = "archive?"; return;
	}

	reportf("PKWare ZIP %s archive v%d.%d, ",
		c, h.version / 10, h.version % 10);

	if (h.fnlength > 0) {
		fn = malloc(h.fnlength + 1);
		_ddread(fn, h.fnlength);
		*(fn + h.fnlength) = '\0';
		printf("\"%s\", ", fn);
	}

	_printfd(h.csize);
	putchar('/');
	_printfd(h.usize);

	if (h.flag & ENCRYPTED)
		printl(", encrypted");
	if (h.flag & STRONG_ENCRYPTION)
		printl(", strong encryption");
	if (h.flag & COMPRESSED_PATCH)
		printl(", compression patch");
	if (h.flag & ENHANCED_DEFLATION)
		printl(", enhanced deflation");

	putchar('\n');

	if (More) {
		printf(
			"Version    : %d\n"
			"Flag       : %Xh\n"
			"Compression: %Xh\n"
			"Time       : %Xh\n"
			"Date       : %Xh\n"
			"CRC32      : %Xh\n"
			"Size (Uncompressed): %d\n"
			"Size (Compressed)  : %d\n"
			"Filename Size      : %d\n"
			"Extra field Size   : %d\n",
			h.version, h.flag, h.compression,
			h.time, h.date, h.crc32,
			h.usize, h.csize, h.fnlength,
			h.eflength
		);
	}

	free(fn);
}