#include <stdio.h>
#include "../ff.h"
#include "../utils.h"
#include "../settings.h"
#include "ps.h"

// http://www.adobe.com/devnet-apps/photoshop/fileformatashtml/#50577409_19840
void scan_ps() { // big-endian
	struct psd_hdr h;
	_ddread(&h, sizeof(h));
	reportf("Photoshop image v%d, %d x %d, %d-bit ",
		bswap16(h.version), bswap32(h.width),
		bswap32(h.height), bswap16(h.depth));
	switch (bswap16(h.colormode)) {
	case 0: printl("Bitmap"); break;
	case 1: printl("Grayscale"); break;
	case 2: printl("Indexed"); break;
	case 3: printl("RGB"); break;
	case 4: printl("CMYK"); break;
	case 7: printl("Multichannel"); break;
	case 8: printl("Duotone"); break;
	case 9: printl("Lab"); break;
	default: printl("type?"); break;
	}
	printf(", %d channel(s)\n", bswap16(h.channels));
}