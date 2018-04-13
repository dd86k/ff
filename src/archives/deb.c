#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "deb.h"

void _debslice(char *in, char *out, size_t max) {
	size_t i = 0;
	while (in[i] != ' ' && i < max) { ++i; }
	memcpy(out, in, i);
	*(out + i + 1) = '\0';
}

void scan_deb() {
	struct deb_hdr h;
	_ddread(&h, sizeof(h));
	if (strncmp(h.file_iden, DEBIANBIN, sizeof(DEBIANBIN))) {
		report_text();
		return;
	}
	reportn("Debian package v");
	printf("%.3s", h.version);
	if (More) {
		struct deb_data_hdr dh;
		char *e;
		long _os = strtol(h.ctl_filesize, &e, 10);
		_ddread(&dh, sizeof(dh));
		long size = strtol(dh.filesize, &e, 10);
		char fs[20], fe[20];
		_debslice(h.ctl_file_ident, fs, sizeof(h.ctl_file_ident));
		_debslice(dh.file_ident, fe, sizeof(dh.file_ident));
		printf(", %s:", fs);
		_printfd(_os);
		printf(", %s:", fe);
		_printfd(size);
	}

	puts("");
}