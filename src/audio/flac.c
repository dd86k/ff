#include <stdio.h>
#include "../ff.h"
#include "../utils.h"
#include "../settings.h"
#include "flac.h"

// https://xiph.org/flac/format.html
// https://xiph.org/flac/api/format_8h_source.html
// 

void scan_flac() { // big endian
	struct flac_hdr h;
	_osread(&h, sizeof(h));

	if ((uint8_t)h.header) { // & 0xFF != 0
		report("FLAC audio?");
		return;
	}
	int bits = ((h.data[8] & 1) << 4 | (h.data[9] >> 4)) + 1;
	int chan = ((h.data[8] >> 1) & 7) + 1;
	int rate = ((h.data[6] << 12) | h.data[7] << 4 | h.data[8] >> 4);
	reportf("FLAC audio, %u Hz, %u-bit, %u channels\n", rate, bits, chan);
	if (More)
		print_a("MD5: ", h.md5, sizeof(h.md5));
}