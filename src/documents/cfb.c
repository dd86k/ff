#include <stdio.h>
#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "cfb.h"

void scan_cfb() { //TODO: Detect DOC files
	struct cfb_header h;
	_ddread(&h, sizeof(h));
	reportf("Compound File Binary document v%d.%d, %d FAT sectors\n",
		h.major, h.minor, h.fat_sectors);
	if (More) {
		printf(
			"%d directory sectors at %Xh\n"
			"Transaction signature: %Xh\n"
			"DIFAT sectors: %d@%Xh\n"
			"%d mini FAT sectors at %Xh\n",
			h.dir_sectors, h.first_dir_sector,
			h.trans_sig,
			h.difat_sectors, h.first_difat_loc,
			h.mini_fat_sectors, h.first_mini_fat_loc
		);
	}
}