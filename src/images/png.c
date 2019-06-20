#include <stdio.h>
#include "../ff.h"
#include "../utils.h"
#include "../settings.h"
#include "png.h"

void scan_png() {
	struct ihdr_chunk_full h;
	_osseek(16, SEEK_SET); // Magic!
	_osread(&h, sizeof(h));

	reportf("Portable Network Graphics image, %u x %u pixels, ",
		bswap32(h.width), bswap32(h.height));

	switch (h.color) {
	case 0:
		switch (h.depth) {
		case 1: case 2: case 4: case 8: case 16:
			printf("%u-bit grayscale\n", h.depth);
			break;
		default: puts("grayscale?");
		}
		break;
	case 2:
		switch (h.depth) {
		case 8: case 16:
			printf("%u-bit RGB\n", h.depth * 3);
			break;
		default: puts("rgb?");
		}
		break;
	case 3:
		switch (h.depth) {
		case 1: case 2: case 4: case 8:
			printf("8-bit PLTE Palette (%u)\n", h.depth);
			break;
		default: puts("plte?");
		}
		break;
	case 4:
		switch (h.depth) {
		case 8: case 16:
			printf("%u-bit grayscale+alpha\n", h.depth);
			break;
		default: puts("grayscale+alpha?");
		}
		break;
	case 6:
		switch (h.depth) {
		case 8: case 16:
			printf("32-bit RGBA (%u)\n", h.depth);
			break;
		default: puts("rgba?");
		}
		break;
	default: puts("color?");
	}

	if (More) {
		char *c, *f, *i;
		switch (h.compression) {
		case 0:  c = "default"; break;
		default: c = "unknown";
		}

		switch (h.filter) {
		case 0:  f = "default"; break;
		default: f = "unknown";
		}

		switch (h.interlace) {
		case 0:  i = "no"; break;
		case 1:  i = "Adam7"; break;
		default: i = "unknown"; break;
		}

		printf("%s compression, %s filtering, %s interlacing\n",
			c, f, i);
	}
}