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
	
	char *c, *f;
	switch (h.color >> 4) {
	case 0:  c = "YCbCr (BT 709) "; break;
	case 1:  c = "RGB "; break;
	case 2:  c = "YCgCo "; break;
	case 3:  c = "YCbCr (BT 709) "; break;
	case 4:  c = "YCbCr (BT 2020) "; break;
	case 5:  c = "YCbCr (BT 2020, constant) "; break;
	default: c = "color? "; break;
	}

	switch (h.format >> 5) {
	case 0:  f = "Grayscale"; break;
	case 1:  f = "4:2:0 (JPEG)"; break;
	case 2:  f = "4:2:2 (JPEG)"; break;
	case 3:  f = "4:4:4"; break;
	case 4:  f = "4:2:0 (MPEG2)"; break;
	case 5:  f = "4:2:2 (MPEG2)"; break;
	default: f = "format?"; break;
	}

	reportf("Better Portable Graphics (BPG) image, %u x %u, %s, %s",
		width, height, c, f);

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
}