#include <stdio.h>
#include "../ff.h"
#include "../utils.h"
#include "../settings.h"
#include "bpg.h"
#include "image_utils.h"

void scan_bpg(void) {
    struct heic_hdr h;
    _ddread(&h, sizeof(h));

    unsigned int width = fread_l(4);
    unsigned int height = fread_l(4);

    reportn("Better Portable Graphics image, ");

    printf("%d x %d", width, height);

    if (h.format & ALPHA)
        printf(", alpha1");
    if (h.color & ALPHA2) // ?
        printf(", alpha2");
    if (h.color & ANIMATION)
        printf(", animated");
    if (h.color & LIMITED)
        printf(", limited range");
    if (h.color & EXTENSION)
        printf(", w/ data extension");

    puts("");

    if (More) {
        switch (h.color >> 4) {
		default: printf("Unknown color "); break;
		case 0: printf("YCbCr (BT 709) "); break;
		case 1: printf("RGB "); break;
		case 2: printf("YCgCo "); break;
		case 3: printf("YCbCr (BT 709) "); break;
		case 4: printf("YCbCr (BT 2020) "); break;
		case 5: printf("YCbCr (BT 2020, constant) "); break;
        }

        switch (h.format >> 5) {
		default: printf("Unknown format\n"); break;
		case 0: printf("Grayscale\n"); break;
		case 1: printf("4:2:0 (JPEG)\n"); break;
		case 2: printf("4:2:2 (JPEG)\n"); break;
		case 3: printf("4:4:4\n"); break;
		case 4: printf("4:2:0 (MPEG2)\n"); break;
		case 5: printf("4:2:2 (MPEG2)\n"); break;
        }
    }
}