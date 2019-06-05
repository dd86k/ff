#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "deb.h"

void _debslice(char *in, size_t max) {
	if (*(in + max - 1) != ' ') {
		*(in + max - 1) = '\0';
		return;
	}
	while (in[--max] == ' ' && max > 0);
	*(in + max + 1) = '\0';
}

void scan_deb() {
	struct deb_hdr h;
	struct deb_data_hdr dh;

	_osread(&h, sizeof(h));
	if (strncmp(h.file_iden, DEBIANBIN, sizeof(DEBIANBIN) - 1)) {
		report_text();
		return;
	}

	long dfsize = strtol(h.ctl_filesize, NULL, sizeof(h.ctl_filesize));
	if (dfsize) {
		_osseek(dfsize, SEEK_CUR);
		_osread(&dh, sizeof(dh));
	}

	long cfsize = strtol(dh.filesize, NULL, sizeof(dh.filesize));
	_debslice(h.ctl_file_ident, sizeof(h.ctl_file_ident));
	_debslice(dh.file_ident, sizeof(dh.file_ident));

	reportf("Debian package v%.3s, %s (", h.version, h.ctl_file_ident);
	_printfd(dfsize);
	printf("), %s (", dh.file_ident);
	_printfd(cfsize);
	puts(")");
}