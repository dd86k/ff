#include <stdio.h>
#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "szdd.h"

void scan_szdd() {
	struct szdd_hdr h;
	_ddread(&h, sizeof(h));

	reportf("MS-DOS SZDD%s archive, char: %Xh, %d B\n",
		h.compression != 'A' ? "?" : "",
		h.character, h.length);
}