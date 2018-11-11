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
		do { // Skip useless chunks
			_ddread(&s, 4); // Chunk length
			if (_ddseek(s, SEEK_CUR)) {
				report_unknown();
				return;
			}
			_ddread(&s, 4);
		} while (s != FMT_CHUNK);

	struct fmt_chunk h;
	_ddread(&h, sizeof(h));

	char *f, c[11];

	switch (h.format) {
	case PCM:        f = "PCM"; break;
	case IEEE_FLOAT: f = "IEEE Float"; break;
	case ALAW:       f = "8-bit ITU G.711 A-law"; break;
	case MULAW:      f = "8-bit ITU G.711 u-law"; break;
	case EXTENSIBLE: f = "EXTENDED"; break;
	case _MP2:       f = "MPEG-1 Audio Layer II"; break;
	case _G729:      f = "G.729"; break;
	default:         report("WAVE?"); return; // Ends here pal
	}

	switch (h.channels) {
	case 1: ddstrncpy(c, "Mono", 4); break;
	case 2: ddstrncpy(c, "Stereo", 6); break;
	default: snprintf(c, 11, "%d channels", h.channels); break;
	}

	reportf("WAVE audio (%s) %d Hz, %d kbps, %d-bit, %s\n",
		f, h.samplerate, h.datarate / 1024 * 8, h.samplebits, c);

	if (More) {
		uint8_t guid[16];
		_ddseek(8, SEEK_CUR);
		_ddread(guid, sizeof(guid));
		printf("EXTENDED:");
		print_array(guid, sizeof(guid));
		putchar('\n');
	}
}