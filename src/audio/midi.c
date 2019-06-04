#include <stdio.h>
#include "../ff.h"
#include "../utils.h"
#include "midi.h"

void scan_midi() { // Big-endian
	struct midi_hdr h;
	_ddread(&h, sizeof(h));

	char *f;

	switch (h.format) {
	case 0: f = "single track"; break;
	case 0x0100: f = "multiple tracks"; break;
	case 0x0200: f = "multiple songs"; break;
	default: report("MIDI?"); return;
	}

	uint16_t div = bswap16(h.division);

	reportf("MIDI, %s, %u tracks at ", f, bswap16(h.tracks));

	if (div & 0x8000) // Negative, SMPTE units
		printf("%u ticks/frame (SMPTE: %u)\n", (uint8_t)div, div >> 8);
	else // Ticks per beat
		printf("%u ticks/quarter-note\n", div);
}