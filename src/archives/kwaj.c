#include <stdio.h>
#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "kwaj.h"

void scan_kwaj() {
	struct kwaj_hdr h;
	_ddread(&h, sizeof(h));

	reportn("MS-DOS KWAJ archive, ");

	switch (h.method) {
	case 0: printl("uncompressed"); break;
	case 1: printl("FFh-XOR'd data"); break;
	case 2: printl("regular compression"); break;
	case 3: printl("LZ + Huffman \"Jeff Johnson\" compressed"); break;
	case 4: printl("MS-ZIP compressed"); break;
	default: printf("?"); return;
	}

	if (h.offset)
		printf(", offset: %Xh", h.offset);

	if (h.header & (NAME | EXT)) {
		int offset = 0;
		if (h.header & ULENGHT) offset += 4;
		if (h.header & UNKNOWN) offset += 2;
		if (h.header & DLENGHT) offset += 2;

		if (offset)
			_ddseek(offset, SEEK_CUR);

		char s[13]; // 8.3 limit + \0
		_ddread(s, sizeof(s));
		*(s + 12) = '\0';
		printf(", \"%s\"", s);
	}

	putchar('\n');
}