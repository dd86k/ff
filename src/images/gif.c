#include <stdio.h>
#include <math.h>
#include "../ff.h"
#include "../utils.h"
#include "../settings.h"
#include "gif.h"

void scan_gif() {
	struct gif_header h;
	_ddseek(0, SEEK_SET);
	_ddread(&h, sizeof(h));
	reportn("GIF");

	switch (h.version_[1]) { // 87a, 89a, lazy switch
		case '7': printf("87a"); break;
		case '9': printf("89a"); break;
		default: printf(" image, non-supported version\n"); return;
	}

	printf(" image, %d x %d pixels, %d-bit",
		h.width, h.height, ((h.packed >> 4) & 3) + 1);

	if (More) {
		if (h.packed & GLOBAL_COLOR_TABLE) {
			printf(", Global Color Table");
			if (h.packed & 3)
				printf(" of %f bytes", pow(2, ((h.packed & 3) + 1)));
			if (h.packed & SORT_FLAG)
				printf(", Sorted");
			if (h.bgcolor)
				printf(", BG Index of %X", h.bgcolor);
		}

		if (h.aspect)
			printf(", %f pixel ratio (reported)", ((float)h.aspect + 15) / 64);
	}

	puts("");
}