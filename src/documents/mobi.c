#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "mobi.h"
#include <stdio.h>

// Print name from PalmDB-like file
void palmdb_name() {
	char name[32];
	_ddseek(0, SEEK_SET);
	_ddread(name, sizeof(name));
	printf(" \"%s\"\n", name);
}

void scan_mobi() { // Big-endian
	struct palmdoc_hdr h;
	struct mobi_hdr mh;
	_ddseek(STARTPOS, SEEK_SET);
	_ddread(&h, sizeof(h) + sizeof(mh));

	reportn("Mobipocket ");

	switch (mh.Type) {
	case 0xE8000000: // 232
	case 0x02000000: // 2
		printl("ebook");
		break;
	case 0x03000000: // 3
		printl("PalmDoc ebook");
		break;
	case 0x04000000: // 4
		printl("audio");
		break;
	case 0xF8000000: // 248
		printl("KF8");
		break;
	case 0x01010000: // 257
		printl("News");
		break;
	case 0x02010000: // 258
		printl("News feed");
		break;
	case 0x03010000: // 259
		printl("News magazine");
		break;
	case 0x01020000: // 513
		printl("PICS");
		break;
	case 0x02020000: // 514
		printl("WORD");
		break;
	case 0x03020000: // 515
		printl("XLS");
		break;
	case 0x04020000: // 516
		printl("PPT");
		break;
	case 0x05020000: // 517
		printl("TEXT");
		break;
	case 0x06020000: // 518
		printl("HTML");
		break;
	default:
		printl("?");
		break;
	}

	printl(" document");

	if (h.Compression == 0x0100)
		printl(", PalmDOC compressed");
	else if (h.Compression == 0x4844)
		printl(", HUFF/CDIC compressed");

	if (h.Encryption == 0x0100)
		printl(", Legacy Mobipocket encryption");
	else if (h.Encryption == 0x0200)
		printl(", Mobipocket encryption");

	palmdb_name();
}

void scan_palmdoc() {
    struct palmdoc_hdr h;
    _ddread(&h, sizeof(h));

    reportn("Palm document");

    if (h.Compression == 0x0100) // Big Endian
        printl(", PalmDOC compressed");
    else if (h.Compression == 0x4844) // 17480
        printl(", HUFF/CDIC compressed");

    palmdb_name();
}