#include <stdio.h>
#include "../ff.h"
#include "../utils.h"
#include "../settings.h"
#include "ps.h"

// http://www.adobe.com/devnet-apps/photoshop/fileformatashtml/#50577409_19840
void scan_ps() { // big-endian
	struct psd_hdr h;
	_ddread(&h, sizeof(h));

	char *c;

	switch (bswap16(h.colormode)) {
	case 0:  c = "Bitmap"; break;
	case 1:  c = "Grayscale"; break;
	case 2:  c = "Indexed"; break;
	case 3:  c = "RGB"; break;
	case 4:  c = "CMYK"; break;
	case 7:  c = "Multichannel"; break;
	case 8:  c = "Duotone"; break;
	case 9:  c = "Lab"; break;
	default: c = "type?"; break;
	}

	reportf("Photoshop image v%d, %d x %d, %d-bit %s, %d channels\n",
		bswap16(h.version), bswap32(h.width),
		bswap32(h.height), bswap16(h.depth),
		c, bswap16(h.channels));
}