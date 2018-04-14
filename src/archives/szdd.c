#include <stdio.h>
#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "szdd.h"

void scan_szdd() {
	struct szdd_hdr h;
	_ddread(&h, sizeof(h));

	reportn("MS-DOS SZDD");
	if (h.compression != 'A') printl("? ");
	puts("archive");
}