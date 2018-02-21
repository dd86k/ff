#include <stdio.h>
#include "../ff.h"
#include "../utils.h"
#include "../settings.h"
#include "ps.h"

// http://www.adobe.com/devnet-apps/photoshop/fileformatashtml/#50577409_19840
void scan_ps() { // big-endian
	struct psd_hdr h;
	_ddread(&h, sizeof(h));
	reportn("Photoshop image v");
	printf("%d, %d x %d, %d-bit ",
		bswap16(h.version), bswap32(h.width),
		bswap32(h.height), bswap16(h.depth));
	switch (bswap16(h.colormode)) {
	case 0: printf("Bitmap"); break;
	case 1: printf("Grayscale"); break;
	case 2: printf("Indexed"); break;
	case 3: printf("RGB"); break;
	case 4: printf("CMYK"); break;
	case 7: printf("Multichannel"); break;
	case 8: printf("Duotone"); break;
	case 9: printf("Lab"); break;
	default: printf("type?"); break;
	}
	printf(", %d channel(s)\n", bswap16(h.channels));
}