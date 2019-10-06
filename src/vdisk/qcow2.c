#include <stdio.h>
#include "../ff.h"
#include "../utils.h"
#include "../settings.h"
#include "qcow2.h"

//https://people.gnome.org/~markmc/qcow-image-format.html
//http://git.qemu-project.org/?p=qemu.git;a=blob;f=docs/specs/qcow2.txt

void scan_qcow2(void) {
	struct QCowHeader h;
	_osread(&h, sizeof(h));

	char *c;
	switch (bswap32(h.crypt_method)) {
	case C_AES: c = "AES"; break;
	default: c = "no";
	}

	reportf("QEMU QCOW2 vdisk v%u, %s encryption, ", bswap32(h.version), c);
	_printfd(bswap64(h.size));

	putchar('\n');

	if (More) {
		printf(
			"Number of snapshots: %u\n",
			bswap32(h.nb_snapshots)
		);
	}
}