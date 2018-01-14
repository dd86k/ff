#include <stdio.h>
#include "../ff.h"
#include "../utils.h"
#include "../settings.h"
#include "wav.h"

// http://www-mmsp.ece.mcgill.ca/Documents/AudioFormats/WAVE/WAVE.html
void scan_wav() {
	unsigned int s;
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
	reportn("WAVE audio (");
	switch (h.format) {
	case PCM: printf("PCM"); break;
	case IEEE_FLOAT: printf("IEEE Float"); break;
	case ALAW: printf("8-bit ITU G.711 A-law"); break;
	case MULAW: printf("8-bit ITU G.711 u-law"); break;
	case EXTENSIBLE: printf("EXTENDED"); break;
	case _MP2: printf("MPEG-1 Audio Layer II"); break;
	default: puts("Unknown type)"); return; // Ends here pal
	}
	printf(") %d Hz, %d kbps, %d-bit, ",
		h.samplerate, h.datarate / 1024 * 8, h.samplebits);
	switch (h.channels) {
	case 1: puts("Mono"); break;
	case 2: puts("Stereo"); break;
	default: printf("%d channels\n", h.channels); break;
	}
	if (More) {
		unsigned char guid[16];
		_ddseek(8, SEEK_CUR);
		_ddread(&guid, sizeof(guid));
		printf("EXTENDED:");
		print_array(guid, sizeof(guid));
	}
}