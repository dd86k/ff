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
	case 0: r = "no"; break;
	case 1: r = "FFh-XOR"; break;
	case 2: r = "regular"; break;
	case 3: r = "LZ + Huffman \"Jeff Johnson\""; break;
	case 4: r = "MS-ZIP"; break;
	default: report("MS-DOS KWAJ archive?"); return;
	}

	reportf("MS-DOS KWAJ archive, %s compression, offset: %Xh");

	if (h.header & (NAME | EXT)) {
		int offset = 0;
		if (h.header & ULENGHT) offset += 4;
		if (h.header & UNKNOWN) offset += 2;
		if (h.header & DLENGHT) offset += 2;

		if (offset)
			_osseek(offset, SEEK_CUR);

		char s[12]; // 8.3 limit + \0
		_osread(s, sizeof(s));
		printf(", \"%.12s\"", s);
	}

	putchar('\n');
}