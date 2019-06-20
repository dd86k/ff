#include <stdio.h>
#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "bzip.h"

// https://sourceware.org/bzip2/1.0.5/bzip2-manual-1.0.5.pdf
// https://github.com/dsnet/compress/blob/master/doc/bzip2-format.pdf

void scan_bzip(uint32_t s) {
	struct hdr_bzip *h = (struct hdr_bzip*)&s;
	char v;
	switch (h->version) {
	case 'h': v = '2'; break;
	case '0': v = '1'; break;
	default:  v = '?';
	}
	printf("bzip%c (bz, bz2) archive, %c00 KB blocks\n", v, h->bsize);
}