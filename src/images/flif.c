#include <stdio.h>
#include "../ff.h"
#include "../utils.h"
#include "../settings.h"
#include "flif.h"
#include "image_utils.h"

void scan_flif() {
	struct flif_hdr h;
	_osread(&h, sizeof(h));

	int width = fread_l(4) + 1;
	int height = fread_l(4) + 1;
	//uint8_t animf;
	//_osread(&animf, 1);
	//const int animf = fread_l + 1; // animation frames

	reportf("Free Lossless Image Format (FLIF) image, %u x %u", width, height);

	int lt = h.type & 0xF;
	switch (lt) {
	case 1: printl(", Grayscale"); break;
	case 3: printl(", RGB"); break;
	case 4: printl(", RGBA"); break;
	default: printf(", %u channels", lt);
	}

	char *t;
	switch (h.type >> 4) {
	case 3:  t = ", image"; break;
	case 4:  t = ", interlaced"; break;
	case 5:  t = ", animated"; break;
	case 6:  t = ", interlaced+animated"; break;
	default: t = ", ?";
	}
	puts(t);
}