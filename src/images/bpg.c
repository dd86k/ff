#include <stdio.h>
#include "../ff.h"
#include "../utils.h"
#include "../settings.h"
#include "bpg.h"
#include "image_utils.h"

void scan_bpg(void) {
	struct heic_hdr h;
	_osread(&h, sizeof(h));

	uint32_t width = fread_l(4);
	uint32_t height = fread_l(4);

	reportf("Better Portable Graphics (BPG) image, %u x %u", width, height);

	if (h.format & ALPHA)
		printl(", alpha1");
	if (h.color & ALPHA2) // ?
		printl(", alpha2");
	if (h.color & ANIMATION)
		printl(", animated");
	if (h.color & LIMITED)
		printl(", limited range");
	if (h.color & EXTENSION)
		printl(", data extension");

	putchar('\n');

	if (More) {
		switch (h.color >> 4) {
		case 0: printl("YCbCr (BT 709) "); break;
		case 1: printl("RGB "); break;
		case 2: printl("YCgCo "); break;
		case 3: printl("YCbCr (BT 709) "); break;
		case 4: printl("YCbCr (BT 2020) "); break;
		case 5: printl("YCbCr (BT 2020, constant) "); break;
		default: printl("color? "); break;
		}

		switch (h.format >> 5) {
		case 0: puts("Grayscale"); break;
		case 1: puts("4:2:0 (JPEG)"); break;
		case 2: puts("4:2:2 (JPEG)"); break;
		case 3: puts("4:4:4"); break;
		case 4: puts("4:2:0 (MPEG2)"); break;
		case 5: puts("4:2:2 (MPEG2)"); break;
		default: puts("format?"); break;
		}
	}
}