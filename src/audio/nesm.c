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
		printf("VRCVI, ");
	if (h.chip & 2)
		printf("VRCVII, ");
	if (h.chip & 4)
		printf("FDS, ");
	if (h.chip & 8)
		printf("MMC5, ");
	if (h.chip & 0x10)
		printf("Namco 106, ");
	if (h.chip & 0x20)
		printf("Sunsoft FME-07, ");

	printf("\"%s - %s\", (c) %s\n",
		h.song_artist,
		h.song_name,
		h.song_copyright);
}