#include <stdio.h>
#include "../ff.h"
#include "../utils.h"
#include "../settings.h"
#include "qed.h"

// http://wiki.qemu-project.org/Features/QED/Specification

void scan_qed() {
	struct qed_hdr h;
	_osread(&h, sizeof(h));

	reportl("QEMU QED vdisk, ");
	_printfd(h.image_size);

	if (h.features & QED_F_BACKING_FILE) {
		_osseek(h.backing_filename_offset, SEEK_SET);
		char buffer[256] = { 0 };
		_osread(&buffer, 256);
		printf(", backing file: %s", buffer);
		if (h.features & QED_F_BACKING_FORMAT_NO_PROBE)
			printl(" (raw)");
	}

	if (h.features & QED_F_NEED_CHECK)
		printl(", check needed");

	putchar('\n');
}