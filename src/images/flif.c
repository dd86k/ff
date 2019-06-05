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

	switch (h.type & 0xF) {
	case 1: printl(", Grayscale"); break;
	case 3: printl(", RGB"); break;
	case 4: printl(", RGBA"); break;
	default: printf(", %u channels", h.type & 0xF);
	}

	switch (h.type >> 4) {
	case 3: puts(", image"); break;
	case 4: puts(", interlaced"); break;
	case 5: puts(", animated"); break;
	case 6: puts(", interlaced+animated"); break;
	default: puts(", ?");
	}
}