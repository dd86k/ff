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
}

void scan_deb() {
	struct deb_hdr h;
	_ddread(&h, sizeof(h));
	if (_strcmp_l(h.file_iden, DEBIANBIN, sizeof(DEBIANBIN))) {
		report_text();
		return;
	}
	char s[4] = { 0 };
	memcpy(s, h.version, 3);
	reportn("Debian package v");
	printf("%s", s);
	if (More) {
		struct deb_data_hdr dh;
		char *e;
		long _os = strtol(h.ctl_filesize, &e, 10);
		_ddseek(_os + 2, SEEK_CUR); // +missing padder
		_ddread(&dh, sizeof(dh));
		long size = strtol(dh.filesize, &e, 10);
		char fs[20];
		char fe[20];
		_debslice(h.ctl_file_ident, fs, sizeof(h.ctl_file_ident));
		_debslice(dh.file_ident, fe, sizeof(dh.file_ident));
		printf(", %s:", fs);
		_printfd(_os);
		printf(", %s:", fe);
		_printfd(size);
		/*try {
			import std.conv : parse;
			string dps = isostr(h.ctl_filesize);
			os = parse!int(dps);
			fseek(fp, os, SEEK_CUR);
			fread(&dh, dh.sizeof, 1, fp);
			string doss = isostr(dh.filesize);
			dos = parse!int(doss);
		} catch (Exception) {
			return;
		}
		writef("%s - %s\n", isostr(h.ctl_file_ident), formatsize(os));
		writef("%s - %s\n", isostr(dh.file_ident), formatsize(dos));*/
	}

	puts("");
}