#include <stdio.h>
#include "../ff.h"
#include "../utils.h"
#include "../settings.h"
#include "wav.h"

// http://www-mmsp.ece.mcgill.ca/Documents/AudioFormats/WAVE/WAVE.html
void scan_wav() {
	uint32_t s;
	_ddread(&s, 4);
	if (s != FMT_CHUNK) // Time to find the right chunk type
		do {
			_ddread(&s, 4); // get chunk length
			if (_ddseek(s, SEEK_CUR)) { // and skip it if possible
				report_unknown();
				return;
			}
			_ddread(&s, 4);
		} while (s != FMT_CHUNK); // Skip useless chunks

	struct fmt_chunk h;
	_ddread(&h, sizeof(h));

	char *f;

	switch (h.format) {
	case PCM:        f = "PCM"; break;
	case IEEE_FLOAT: f = "IEEE Float"; break;
	case ALAW:       f = "G.711 A-law"; break;
	case MULAW:      f = "G.711 u-law"; break;
	case EXTENSIBLE: f = "EXTENDED"; break;
	// Non-standard
	case _MP2:       f = "MPEG-1 Audio Layer II"; break;
	case _G729:      f = "G.729"; break;
	default:         report("WAVE audio?"); return;
	}

	reportf("WAVE audio (%s) %d Hz, %d kbps, %d-bit, %d channels\n",
		f, h.samplerate, h.datarate / 1024 * 8, h.samplebits, h.channels);

	if (More) {
		uint8_t guid[16];
		_ddseek(8, SEEK_CUR);
		_ddread(guid, sizeof(guid));
		printf("EXTENDED:");
		print_array(guid, sizeof(guid));
		putchar('\n');
	}
}