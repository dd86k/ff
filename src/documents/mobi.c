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
		printf("ebook");
		break;
	case 0x03000000: // 3
		printf("PalmDoc ebook");
		break;
	case 0x04000000: // 4
		printf("audio");
		break;
	case 0xF8000000: // 248
		printf("KF8");
		break;
	case 0x01010000: // 257
		printf("News");
		break;
	case 0x02010000: // 258
		printf("News feed");
		break;
	case 0x03010000: // 259
		printf("News magazine");
		break;
	case 0x01020000: // 513
		printf("PICS");
		break;
	case 0x02020000: // 514
		printf("WORD");
		break;
	case 0x03020000: // 515
		printf("XLS");
		break;
	case 0x04020000: // 516
		printf("PPT");
		break;
	case 0x05020000: // 517
		printf("TEXT");
		break;
	case 0x06020000: // 518
		printf("HTML");
		break;
	default:
		printf("?");
		break;
	}

	printf(" document");

	if (h.Compression == 0x0100)
		printf(", PalmDOC compressed");
	else if (h.Compression == 0x4844)
		printf(", HUFF/CDIC compressed");

	if (h.Encryption == 0x0100)
		printf(", Legacy Mobipocket encryption");
	else if (h.Encryption == 0x0200)
		printf(", Mobipocket encryption");

	palmdb_name();
}

void scan_palmdoc() {
    struct palmdoc_hdr h;
    _ddread(&h, sizeof(h));

    reportn("Palm document");

    if (h.Compression == 0x0100) // Big Endian
        printf(", PalmDOC compressed");
    else if (h.Compression == 0x4844) // 17480
        printf(", HUFF/CDIC compressed");

    palmdb_name();
}