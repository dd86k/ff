#include <stdio.h>
#include "../ff.h"
#include "../utils.h"
#include "nesm.h"

void scan_nesm() {
	struct nesm_hdr h;
	_ddread(&h, sizeof(h));

	if (h.flag & 0b10)
		reportn("Dual NTSC/PAL");
	else if (h.flag & 1)
		reportn("NSTC");
	else
		reportn("PAL");

	printf(" Nintendo Sound audio, %d songs, ", h.total_song);

	if (h.chip & 1)
		printl("VRCVI, ");
	if (h.chip & 2)
		printl("VRCVII, ");
	if (h.chip & 4)
		printl("FDS, ");
	if (h.chip & 8)
		printl("MMC5, ");
	if (h.chip & 0x10)
		printl("Namco 106, ");
	if (h.chip & 0x20)
		printl("Sunsoft FME-07, ");

	printf("\"%.32s - %.32s\", (c) %.32s\n",
		h.song_artist,
		h.song_name,
		h.song_copyright);
}