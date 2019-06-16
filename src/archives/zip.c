#include <stdio.h>
#include <stdlib.h>
#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "zip.h"

// https://pkware.cachefly.net/webdocs/APPNOTE/APPNOTE-6.3.6.TXT
// https://support.pkware.com/display/PKZIP/Application+Note+Archives

void scan_zip() {
	struct pkzip_hdr h;
	_osread(&h, sizeof(h));

	char *c, *fn;

	switch (h.compression) {
	case 0: c = "Uncompressed"; break;
	case 1: c = "Shrunk"; break;
	case 2: c = "Reduced (x1)"; break;
	case 3: c = "Reduced (x2)"; break;
	case 4: c = "Reduced (x3)"; break;
	case 5: c = "Reduced (x4)"; break;
	case 6: c = "Imploded"; break;
	case 8: c = "Deflated"; break;
	case 9: c = "Enhanced Deflated"; break;
	case 10: c = "DCL Imploded"; break;
	case 12: c = "BZIP2"; break;
	case 14: c = "LZMA"; break;
	case 16: c = "IBM z/OS CMPSC"; break;
	case 18: c = "IBM TERSE"; break;
	case 19: c = "IBM LZ77 z/Architecture"; break;
	case 96: c = "JPEG variant"; break;
	case 97: c = "WavPack Compressed"; break;
	case 98: c = "PPMd Version I, Rev 1"; break;
	case 99: c = "AE-x Encryption"; break; // AES+CTR+HMAC-SHA1
	default: c = "(?)"; return;
	}

	reportf("PKWare ZIP %s archive v%u.%u, ",
		c, h.version / 10, h.version % 10);

	if (h.fnlength > 0) {
		fn = malloc(h.fnlength + 1);
		_osread(fn, h.fnlength);
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
			"Version    : %u\n"
			"Flag       : %Xh\n"
			"Compression: %Xh\n"
			"Time       : %Xh\n"
			"Date       : %Xh\n"
			"CRC32      : %Xh\n"
			"Size (Uncompressed): %u\n"
			"Size (Compressed)  : %u\n"
			"Filename Size      : %u\n"
			"Extra field Size   : %u\n",
			h.version, h.flag, h.compression,
			h.time, h.date, h.crc32,
			h.usize, h.csize, h.fnlength,
			h.eflength
		);
	}
}