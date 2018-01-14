#include <stdio.h>
#include "../ff.h"
#include "../utils.h"
#include "../settings.h"
#include "png.h"

void scan_png() {
    struct ihdr_chunk_full h;
    _ddseek(16, SEEK_SET); // Magic!
    _ddread(&h, sizeof(h));
    reportn("Portable Network Graphics image, ");

	printf("%d x %d pixels, ", bswap32(h.width), bswap32(h.height));
	switch (h.color) {
	case 0:
		switch (h.depth) {
		case 1: case 2: case 4: case 8: case 16:
			printf("%d", h.depth);
			break;
		default: printf("?"); break;
		}
		printf("-bit Grayscale");
		break;
	case 2:
		switch (h.depth) {
		case 8: case 16:
			printf("%d", h.depth*3);
			break;
		default: printf("?"); break;
		}
		printf("-bit RGB");
		break;
	case 3:
		switch (h.depth) {
		case 1: case 2: case 4: case 8:
			printf("8");
			break;
		default: printf("?"); break;
		}
		printf("-bit PLTE Palette");
		break;
	case 4:
		switch (h.depth) {
		case 8: case 16:
			printf("%d", h.depth);
			break;
		default: printf("?"); break;
		}
		printf("-bit Grayscale+Alpha");
		break;
	case 6:
		switch (h.depth) {
		case 8: case 16:
			printf("32");
			break;
		default: printf("?"); break;
		}
		printf("-bit RGBA");
		break;
	default: printf("?"); break;
	}

	puts("");

	if (More) {
		switch (h.compression) {
		case 0: printf("Default compression"); break;
		default: printf("? compression"); break;
		}

		printf(", ");

		switch (h.filter) {
		case 0: printf("Default filtering"); break;
		default: printf("? filtering"); break;
		}

		printf(", ");

		switch (h.interlace) {
		case 0: printf("No interlacing"); break;
		case 1: printf("Adam7 interlacing"); break;
		default: printf("? interlacing"); break;
		}

		puts("");
	}
}