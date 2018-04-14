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

	_ddread(&h, sizeof(h));
	if (strcmp(h.file_iden, DEBIANBIN) {
		report_text();
		return;
	}
	_ddread(&dh, sizeof(dh));

	long deb_fsize = strtol(h.ctl_filesize, NULL, sizeof(h.ctl_filesize));
	long ctl_fsize = strtol(dh.filesize, NULL, sizeof(dh.filesize));
	_debslice(h.ctl_file_ident, sizeof(h.ctl_file_ident));
	//_debslice(dh.file_ident, sizeof(dh.file_ident));

	reportn("Debian package v");
	printf("%.3s", h.version);
	printf(", %s (", h.ctl_file_ident);
	_printfd(deb_fsize);
	printf("), %s (", dh.file_ident);
	_printfd(ctl_fsize);
	puts(")");
}