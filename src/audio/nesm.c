#include <stdio.h>
#include "../ff.h"
#include "../utils.h"
#include "nesm.h"

void scan_nesm() {
	struct nesm_hdr h;
	_osread(&h, sizeof(h));

	char *r, *c = "?";

	if (h.flag & 0b10)
		r = "Dual NTSC/PAL";
	else if (h.flag & 1)
		r = "NSTC";
	else
		r = "PAL";

	if (h.chip & 1)
		c = "VRCVI";
	if (h.chip & 2)
		c = "VRCVII";
	if (h.chip & 4)
		c = "FDS";
	if (h.chip & 8)
		c = "MMC5";
	if (h.chip & 0x10)
		c = "Namco 106";
	if (h.chip & 0x20)
		c = "Sunsoft FME-07";

	reportf("%s Nintendo Sound audio, %u songs, using %s, "
		"\"%.32s - %.32s\", (c) %.32s\n",
		r, h.total_song, c,
		h.song_artist,
		h.song_name,
		h.song_copyright);
}