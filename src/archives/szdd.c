#include <stdio.h>
#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "szdd.h"

void scan_szdd() {
	struct szdd_hdr h;
	_osread(&h, sizeof(h));

	reportf("MS-DOS SZDD%s archive, char: %Xh, %u B\n",
		h.compression != 'A' ? "?" : "",
		h.character, h.length);
}