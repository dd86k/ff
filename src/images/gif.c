#include <stdio.h>
#include <math.h>
#include "../ff.h"
#include "../utils.h"
#include "../settings.h"
#include "gif.h"

void scan_gif() {
	struct gif_header h;
	_osseek(0, SEEK_SET);
	_osread(&h, sizeof(h));

	switch (h.version_[1]) { // 87a, 89a, lazy switch
	case '7': case '9': break;
	default: report("GIF image"); return;
	}

	reportf("GIF%.3s image, %u x %u pixels, %u-bit\n",
		h.version_, h.width, h.height, ((h.packed >> 4) & 3) + 1);

	if (More) {
		if (h.packed & GLOBAL_COLOR_TABLE) {
			printl("Global Color Table");
			if (h.packed & 3)
				printf(", %u bytes", (int)pow(2, ((h.packed & 3) + 1)));
			if (h.packed & SORT_FLAG)
				printl(", Sorted");
			if (h.bgcolor)
				printf(", BG Index of %u", h.bgcolor);
			putchar('\n');
		}
		if (h.aspect)
			printf("Pixel ratio (reported): %f", ((float)h.aspect + 15) / 64);
	}
}