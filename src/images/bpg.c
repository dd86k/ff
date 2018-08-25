#include <stdio.h>
#include "../ff.h"
#include "../utils.h"
#include "../settings.h"
#include "bpg.h"
#include "image_utils.h"

void scan_bpg(void) {
    struct heic_hdr h;
    _ddread(&h, sizeof(h));

    uint32_t width = fread_l(4);
    uint32_t height = fread_l(4);

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
        printf(", data extension");

    putchar('\n');

    if (More) {
        switch (h.color >> 4) {
		default: printf("color? "); break;
		case 0: printf("YCbCr (BT 709) "); break;
		case 1: printf("RGB "); break;
		case 2: printf("YCgCo "); break;
		case 3: printf("YCbCr (BT 709) "); break;
		case 4: printf("YCbCr (BT 2020) "); break;
		case 5: printf("YCbCr (BT 2020, constant) "); break;
        }

        switch (h.format >> 5) {
		default: puts("format?"); break;
		case 0: puts("Grayscale"); break;
		case 1: puts("4:2:0 (JPEG)"); break;
		case 2: puts("4:2:2 (JPEG)"); break;
		case 3: puts("4:4:4"); break;
		case 4: puts("4:2:0 (MPEG2)"); break;
		case 5: puts("4:2:2 (MPEG2)"); break;
        }
    }
}