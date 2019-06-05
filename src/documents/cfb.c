#include <stdio.h>
#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "cfb.h"

void scan_cfb() {
	struct cfb_header h;
	_osread(&h, sizeof(h));
	reportf("Compound File Binary document v%u.%u, %u FAT sectors\n",
		h.major, h.minor, h.fat_sectors);
	if (More) {
		printf(
			"%u directory sectors at %Xh\n"
			"Transaction signature: %Xh\n"
			"DIFAT sectors: %u@%Xh\n"
			"%u mini FAT sectors at %Xh\n",
			h.dir_sectors, h.first_dir_sector,
			h.trans_sig,
			h.difat_sectors, h.first_difat_loc,
			h.mini_fat_sectors, h.first_mini_fat_loc
		);
	}
}