#include <stdio.h>
#include "../ff.h"
#include "../utils.h"
#include "../settings.h"
#include "flac.h"

//https://xiph.org/flac/format.html
//https://xiph.org/flac/api/format_8h_source.html

void scan_flac() {
	struct flac_hdr h;
	_ddread(&h, sizeof(h));
	reportn("FLAC audio");
	if ((h.header & 0xFF) == 0) { // Big endian on top of this shit
		int bits = ((h.stupid[8] & 1) << 4 | (h.stupid[9] >> 4)) + 1;
		int chan = ((h.stupid[8] >> 1) & 7) + 1;
		int rate =
			((h.stupid[6] << 12) | h.stupid[7] << 4 | h.stupid[8] >> 4);
		printf(", %d Hz, %d-bit, %d channels\n", rate, bits, chan);
		if (More) {
			printf("MD5: ");
			print_array(h.md5, sizeof(h.md5));
		}
	}
	puts("");
}