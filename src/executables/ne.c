#include <stdio.h>
#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "ne.h"

void scan_ne() {
	struct ne_hdr h;
	_ddread(&h, sizeof(h));

	char *t;

	if (h.ne_flags & NENOTP)
		t = "Library";
	else
		t = "Executable";

	reportf("NE %s, for Windows %d.%d", t, h.ne_expver[1], h.ne_expver[0]);

	if (h.ne_flags) {
		if (h.ne_flags & NENONC)
			printl(", non-conform program");
		if (h.ne_flags & NEIERR)
			printl(", errors in image");
		if (h.ne_flags & NEPROT)
			printl(", runs in protected mode");
		if (h.ne_flags & NEREAL)
			printl(", runs in real mode");
		if (h.ne_flags & NEINST)
			printl(", instance data");
		if (h.ne_flags & NESOLO)
			printl(", solo data");
	}

	putchar('\n');

	if (More) {
		printf(
			"ne_ver         : %Xh\n"
			"ne_rev         : %Xh\n"
			"ne_enttab      : %Xh\n"
			"ne_cbenttab    : %Xh\n"
			"ne_crc         : %Xh\n"
			"ne_flags       : %Xh\n"
			"ne_autodata    : %Xh\n"
			"ne_heap        : %Xh\n"
			"ne_stack       : %Xh\n"
			"ne_csip        : %Xh\n"
			"ne_sssp        : %Xh\n"
			"ne_cseg        : %Xh\n"
			"ne_cmod        : %Xh\n"
			"ne_cbnrestab   : %Xh\n"
			"ne_segtab      : %Xh\n"
			"ne_rsrctab     : %Xh\n"
			"ne_restab      : %Xh\n"
			"ne_modtab      : %Xh\n"
			"ne_imptab      : %Xh\n"
			"ne_nrestab     : %Xh\n"
			"ne_cmovent     : %Xh\n"
			"ne_align       : %Xh\n"
			"ne_cres        : %Xh\n"
			"ne_psegcsum    : %Xh\n"
			"ne_pretthunks  : %Xh\n"
			"ne_psegrefbytes: %Xh\n"
			"ne_swaparea    : %Xh\n"
			"ne_expver      : %Xh, %Xh\n",
			h.ne_ver, h.ne_rev, h.ne_enttab, h.ne_cbenttab,
			h.ne_crc, h.ne_flags, h.ne_autodata, h.ne_heap,
			h.ne_stack, h.ne_csip, h.ne_sssp, h.ne_cseg,
			h.ne_cmod, h.ne_cbnrestab, h.ne_segtab, h.ne_rsrctab,
			h.ne_restab, h.ne_modtab, h.ne_imptab, h.ne_nrestab,
			h.ne_cmovent, h.ne_align, h.ne_cres, h.ne_psegcsum,
			h.ne_pretthunks, h.ne_psegrefbytes, h.ne_swaparea,
			h.ne_expver[0], h.ne_expver[1]
		);
	}
}
