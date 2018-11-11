#include <stdio.h>
#include "../ff.h"
#include "../utils.h"
#include "../settings.h"
#include "png.h"

void scan_png() {
	struct ihdr_chunk_full h;
	_ddseek(16, SEEK_SET); // Magic!
	_ddread(&h, sizeof(h));

	reportf("Portable Network Graphics image, %d x %d pixels, ",
		bswap32(h.width), bswap32(h.height));

	switch (h.color) {
	case 0:
		switch (h.depth) {
		case 1: case 2: case 4: case 8: case 16:
			printf("%d", h.depth);
			break;
		default: putchar('?'); break;
		}
		printl("-bit Grayscale");
		break;
	case 2:
		switch (h.depth) {
		case 8: case 16:
			printf("%d", h.depth*3);
			break;
		default: putchar('?'); break;
		}
		printl("-bit RGB");
		break;
	case 3:
		switch (h.depth) {
		case 1: case 2: case 4: case 8:
			printl("8");
			break;
		default: putchar('?'); break;
		}
		printl("-bit PLTE Palette");
		break;
	case 4:
		switch (h.depth) {
		case 8: case 16:
			printf("%d", h.depth);
			break;
		default: putchar('?'); break;
		}
		printl("-bit Grayscale+Alpha");
		break;
	case 6:
		switch (h.depth) {
		case 8: case 16:
			printl("32");
			break;
		default: putchar('?'); break;
		}
		printl("-bit RGBA");
		break;
	default: putchar('?'); break;
	}

	putchar('\n');

	if (More) {
		switch (h.compression) {
		case 0: printl("Default compression, "); break;
		default: printl("compression?, "); break;
		}

		switch (h.filter) {
		case 0: printl("Default filtering, "); break;
		default: printl("filtering?, "); break;
		}

		switch (h.interlace) {
		case 0: printl("No interlacing"); break;
		case 1: printl("Adam7 interlacing"); break;
		default: printl("interlacing?"); break;
		}

		putchar('\n');
	}
}