#include <stdio.h>
#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "kwaj.h"

void scan_kwaj() {
	struct kwaj_hdr h;
	_ddread(&h, sizeof(h));

	reportn("MS-DOS ");

	switch (h.method) {
	case 0: printf("non-compressed"); break;
	case 1: printf("FFh-XOR'd data"); break;
	case 2: printf("regular SZDD compressed"); break;
	case 3: printf("LZ + Huffman \"Jeff Johnson\" compressed"); break;
	case 4: printf("MS-ZIP compressed"); break;
	default: printf("?");
	}

	printf(" archive (KWAJ)");

	if (h.offset)
		printf(", offset: %Xh", h.offset);

	if (h.header & NAME || h.header & EXT) {
		int offset = 0;
		if (h.header & ULENGHT) offset += 4;
		if (h.header & UNKNOWN) offset += 2;
		if (h.header & DLENGHT) offset += 2;

		if (offset)
			_ddseek(offset, SEEK_CUR);

		char s[12] = { 0 }; // 8.3 limit + \0
		_ddread(&s, sizeof(s));
		printf(", \"%s\"", s);
	}

	puts("");
}