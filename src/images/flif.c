#include <stdio.h>
#include "../ff.h"
#include "../utils.h"
#include "../settings.h"
#include "flif.h"
#include "image_utils.h"

void scan_flif() {
    struct flif_hdr h;
    _ddread(&h, sizeof(h));

    int width = fread_l(4) + 1;
    int height = fread_l(4) + 1;
    //unsigned char animf;
	//_ddread(&animf, 1);
    //const int animf = fread_l + 1; // animation frames

    reportn("Free Lossless Image Format image, ");

    printf("%d x %d, ", width, height);

	switch (h.type & 0xF) {
	case 1: printf("Grayscale, "); break;
	case 3: printf("RGB, "); break;
	case 4: printf("RGBA, "); break;
	default: printf("%d channels, ", h.type & 0xF);
	}

    switch (h.type >> 4) {
	//case 3: printf(""); break; // Still image
	case 4: puts("interlaced"); break;
	case 5: puts("animated"); break;
	case 6: puts("interlaced, animated"); break;
	default: puts("?"); return;
    }
}