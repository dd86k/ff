#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "zip.h"
#include <stdio.h>
#include <stdlib.h>

void scan_zip() {
	struct pkzip_hdr h;
	_ddread(&h, sizeof(h));

	reportn("PKWare ZIP ");

	switch (h.compression) {
	case 0: printf("Uncompressed"); break;
	case 1: printf("Shrunk"); break;
	case 2: case 3: case 4:
	case 5: printf("Reduced by %d", h.compression - 1); break;
	case 6: printf("Imploded"); break;
	case 8: printf("Deflated"); break;
	case 9: printf("Enhanced Deflated"); break;
	case 10: printf("DCL Imploded (PKWare)"); break;
	case 12: printf("BZIP2"); break;
	case 14: printf("LZMA"); break;
	case 18: printf("IBM TERSE"); break;
	case 19: printf("IBM LZ77 z"); break;
	case 98: printf("PPMd Version I, Rev 1"); break;
	default: printf("(Unknown type)"); return;
	}

	printf(" archive v%d.%d, ", h.version / 10, h.version % 10);

	if (h.fnlength > 0) {
		char *file = (char*)malloc(h.fnlength + 1);
		_ddread(file, h.fnlength);
		printf("\"%s\", ", file);
	}

	_printfd(h.csize);
	printf("/");
	_printfd(h.usize);

	if (h.flag & ENCRYPTED)
		printf(", encrypted");
	if (h.flag & STRONG_ENCRYPTION)
		printf(", strong encryption");
	if (h.flag & COMPRESSED_PATCH)
		printf(", compression patch");
	if (h.flag & ENHANCED_DEFLATION)
		printf(", enhanced deflation");

	puts("");

	if (More) {
		printf(
			"Version    : %X\n"
			"Flag       : %X\n"
			"Compression: %X\n"
			"Time       : %X\n"
			"Date       : %X\n"
			"CRC32      : %X\n"
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