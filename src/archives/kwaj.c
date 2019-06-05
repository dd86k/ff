#include <stdio.h>
#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "kwaj.h"

void scan_kwaj() {
	struct kwaj_hdr h;
	_osread(&h, sizeof(h));

	char *r;

	switch (h.method) {
	case 0: r = "uncompressed"; break;
	case 1: r = "FFh-XOR'd data"; break;
	case 2: r = "regular compression"; break;
	case 3: r = "LZ + Huffman \"Jeff Johnson\" compressed"; break;
	case 4: r = "MS-ZIP compressed"; break;
	default: report("MS-DOS KWAJ archive?"); return;
	}

	reportf("MS-DOS KWAJ archive, %s, offset: %Xh");

	if (h.header & (NAME | EXT)) {
		int offset = 0;
		if (h.header & ULENGHT) offset += 4;
		if (h.header & UNKNOWN) offset += 2;
		if (h.header & DLENGHT) offset += 2;

		if (offset)
			_osseek(offset, SEEK_CUR);

		char s[13]; // 8.3 limit + \0
		_osread(s, sizeof(s));
		*(s + 12) = '\0';
		printf(", \"%s\"", s);
	}

	putchar('\n');
}