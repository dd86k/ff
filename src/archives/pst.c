#include <stdio.h>
#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "pst.h"

void scan_pst() {
	struct pst_header h;
	struct pst_unicode uh;
	_ddread(&h, sizeof(h));
	char ansi = 0;
	char unicode = 0;

	if (h.version_ == 14 || h.version_ == 15) {
		ansi = 1;
		struct pst_ansi ah;
		_ddread(&ah, sizeof(ah));
		uh.crypt = ah.crypt;
	} else if (h.version_ >= 23) {
		unicode = 1;
		_ddread(&uh, sizeof(uh));
	}

	char *a, *c;

	if (ansi)
		a = "ANSI, ";
	else if (unicode)
		a = "Unicode, ";

	switch (uh.crypt) {
	case 0x01: c = "encrypted (Permutation algorithm)"; break;
	case 0x02: c = "encrypted (Cyclic algorithm)"; break;
	case 0x10: c = "encrypted (Windows Information Protection)"; break;
	default:   c = "unencrypted";
	}

	reportf("PST archive, v%d (client v%d), %s, %s\n",
		h.version_, h.client_version, a, c);

	if (More) {
		printf(
			"CRC32: %08X\n"
			"client_magic: %Xh\n"
			"file_version: %Xh\n"
			"client_version: %Xh\n"
			"platform_create: %Xh\n"
			"platform_access: %Xh\n",
			h.crc,
			h.client,
			h.version_,
			h.client_version,
			h.platform_create,
			h.platform_access
		);
		if (unicode) {
			printf(
				"crc full: %08X\n"
				"nextp: %llXh\n"
				"unique: %Xh\n",
				uh.crcfull, uh.nextp, uh.unique
			);
		}
	}
}