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

	reportf("MIDI, %s, %d tracks at ", f, bswap16(h.tracks));

	if (div & 0x8000) // Negative, SMPTE units
		printf("%d ticks/frame (SMPTE: %d)\n", div & 0xFF, div >> 8 & 0xFF);
	else // Ticks per beat
		printf("%d ticks/quarter-note\n", div);
}