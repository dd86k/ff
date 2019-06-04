#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "mobi.h"
#include <stdio.h>

// Print name from PalmDB-like file
//TODO: pass a pointer and copy the string directly for reportf usage
void palmdb_name() {
	char name[32];
	_ddseek(0, SEEK_SET);
	_ddread(name, sizeof(name));
	printf(", \"%.32s\"\n", name);
}

void scan_mobi() { // Big-endian
	struct palmdoc_hdr h;
	struct mobi_hdr mh;
	_ddseek(STARTPOS, SEEK_SET);
	_ddread(&h, sizeof(h) + sizeof(mh));

	char *r;

	switch (mh.Type) {
	case 0xE8000000: // 232
	case 0x02000000: // 2
		r = "ebook";
		break;
	case 0x03000000: // 3
		r = "PalmDoc ebook";
		break;
	case 0x04000000: // 4
		r = "audio";
		break;
	case 0xF8000000: // 248
		r = "KF8";
		break;
	case 0x01010000: // 257
		r = "News";
		break;
	case 0x02010000: // 258
		r = "News feed";
		break;
	case 0x03010000: // 259
		r = "News magazine";
		break;
	case 0x01020000: // 513
		r = "PICS";
		break;
	case 0x02020000: // 514
		r = "WORD";
		break;
	case 0x03020000: // 515
		r = "XLS";
		break;
	case 0x04020000: // 516
		r = "PPT";
		break;
	case 0x05020000: // 517
		r = "TEXT";
		break;
	case 0x06020000: // 518
		r = "HTML";
		break;
	default:
		r = "?";
		break;
	}

	char *c, *e;

	switch (h.Compression) {
	case 0x0100: c = "PalmDOC"; break;
	case 0x4844: c = "HUFF/CDIC"; break;
	default: c = "no";
	}

	switch (h.Encryption) { // Looks like encryption version
	case 0x0100: e = "Legacy Mobipocket"; break;
	case 0x0200: e = "Mobipocket"; break;
	default: e = "no";
	}

	reportf("Mobipocket %s document, %s compression, %s encryption",
		r, c, e);
	palmdb_name();
}

void scan_palmdoc() {
	struct palmdoc_hdr h;
	_ddread(&h, sizeof(h));

	reportl("Palm document");

	if (h.Compression == 0x0100) // Big Endian
		printl(", PalmDOC compressed");
	else if (h.Compression == 0x4844) // 17480
		printl(", HUFF/CDIC compressed");

	palmdb_name();
}