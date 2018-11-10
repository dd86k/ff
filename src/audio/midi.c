#include <stdio.h>
#include "../ff.h"
#include "../utils.h"
#include "midi.h"

void scan_midi() { // Big-endian
	struct midi_hdr h;
	_ddread(&h, sizeof(h));

	reportn("MIDI ");

	switch (h.format) {
	case 0: printl("Single track"); break;
	case 0x0100: printl("Multiple tracks"); break;
	case 0x0200: printl("Multiple songs"); break;
	default: putchar('?'); return;
	}

	uint16_t div = bswap16(h.division);
	printf(", %d tracks at ", bswap16(h.number));
	if (div & 0x8000) // Negative, SMPTE units
		printf("%d ticks/frame (SMPTE: %d)\n", div & 0xFF, div >> 8 & 0xFF);
	else // Ticks per beat
		printf("%d ticks/quarter-note\n", div);
}