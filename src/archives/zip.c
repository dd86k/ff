#include <stdio.h>
#include <stdlib.h>
#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "zip.h"

void scan_zip() {
	struct pkzip_hdr h;
	_ddread(&h, sizeof(h));

	reportn("PKWare ZIP ");

	switch (h.compression) {
	case 0: printl("Uncompressed"); break;
	case 1: printl("Shrunk"); break;
	case 2: case 3: case 4: case 5:
		printf("Reduced by %d", h.compression - 1); break;
	case 6: printl("Imploded"); break;
	case 8: printl("Deflated"); break;
	case 9: printl("Enhanced Deflated"); break;
	case 10: printl("DCL Imploded"); break;
	case 12: printl("BZIP2"); break;
	case 14: printl("LZMA"); break;
	case 18: printl("IBM TERSE"); break;
	case 19: printl("IBM LZ77 z"); break;
	case 98: printl("PPMd Version I, Rev 1"); break;
	default: printl("archive?"); return;
	}

	printf(" archive v%d.%d, ", h.version / 10, h.version % 10);

	if (h.fnlength) {
		char *fn = malloc(h.fnlength + 1);
		_ddread(fn, h.fnlength);
		*(fn + h.fnlength) = '\0';
		printf("\"%s\", ", fn);
		free(fn);
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
}