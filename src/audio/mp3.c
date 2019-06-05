#include <stdio.h>
#include <stdlib.h>
#include "../ff.h"
#include "../utils.h"
#include "mp3.h"

// MPEG-1: ISO/IEC 11172-3
// MPEG-2: ISO/IEC 13818-3
// ID3v1: http://www.mpgedit.org/mpgedit/mpeg%5Fformat/mpeghdr.htm
// ID3V2: http://id3.org/

void scan_mp3(uint32_t sig, int id3) {
	char bv1l1[16][8] = {
		"free", "32", "64", "96", "128", "160", "192", "224",
		"256", "288", "320", "352", "384", "416", "448", "bad"
	};
	char bv1l2[16][8] = {
		"free", "32", "48", "56", "64", "80", "96", "112",
		"128", "160", "192", "224", "256", "320", "384", "bad"
	};
	char bv1l3[16][8] = {
		"free", "32", "40", "48", "56", "64", "80", "96",
		"112", "128", "160", "192", "224", "256", "320", "bad"
	};
	char bv2l1[16][8] = {
		"free", "32", "48", "56", "64", "80", "96", "112",
		"128", "144", "160", "176", "192", "224", "256", "bad"
	};
	char bv2l23[16][8] = {
		"free", "8", "16", "24", "32", "40", "48", "56",
		"64", "80", "96", "112", "128", "144", "160", "bad"
	};
	char fv1[4][8] = {
		"44100", "48000", "32000", "(res.)"
	};
	char fv2[4][8] = {
		"22050", "24000", "16000", "(res.)"
	};
	/*char fv25[4][8] = {
		"11025", "12000", "8000", "(res.)"
	};*/
	char ca[4][8] = {
		"stereo", "joint", "dual", "mono"
	};

	struct mp3_hdr h = *(struct mp3_hdr*)&sig;

	char v = h.sig & 0x800 ? '1' : '2'; /// MPEG version
	char *l; // layer
	char *b; // bitrate
	char *f; // frequency
	char *c; // channels
	size_t bi = h.info >> 4; // bitrate index
	size_t fi = (h.info >> 2) & 3; // frequency index
	size_t ci = (h.extra >> 6); // channel index
	char li; // layer index, only for mode extension

	switch (h.sig & 0x600) {
	case 0x200:
		li = 3;
		l = "III";
		b = v == '2' ? bv2l23[bi] : bv1l3[bi];
		break;
	case 0x400:
		li = 2;
		l = "II";
		b = v == '2' ? bv2l23[bi] : bv1l2[bi];
		break;
	case 0x600:
		li = 1;
		l = "I";
		b = v == '2' ? bv2l1[bi] : bv1l1[bi];
		break;
	default:
		li = 0; l = "(res.)"; b = "(res.)";
		break;
	}
	f = v == '2' ? fv2[fi] : fv1[fi];
	c = ca[ci];

	reportf(
		"MPEG-%c Audio Layer %s (MP3) audio, %s Hz, %s kbps, %s",
		v, l, f, b, c
	);
	if (ci == 1) { // joint stereo audio, regardless of version
		switch (li) { // layer
		case 3:
			if (h.extra & 0x20)
				printl(" +intensity");
			if (h.extra & 0x10)
				printl(" +ms");
			break;
		case 2: case 1:
			switch (h.extra & 0x30) {
			case 0:    printl(" (band 4-31)"); break;
			case 0x10: printl(" (band 8-31)"); break;
			case 0x20: printl(" (band 12-31)"); break;
			case 0x30: printl(" (band 16-31)"); break;
			}
			break;
		}
	}
	switch (id3) {
	case 2: printl(", id3v2"); break;
	case 1: printl(", id3v1"); break;
	}
	if (h.sig & 0x100)
		printl(", crc16");
	if (h.info & 1)
		printl(", pbit");
	if (h.info & 2)
		printl(", pad");
	if (h.extra & 8)
		printl(", copyright");
	if (h.extra & 6)
		printl(", original");
	switch (h.extra & 3) {
	case 1: printl(", 50/15 ms\n"); return;
	case 3: printl(", CCIT J.17\n"); return;
	}
	putchar('\n');
}

// returns non-zero if 4-byte sig is mp3, LSB only
int check_mp3(uint32_t s) {
	return (bswap16(s) >> 4) == 0xFFF;
}

// skip ID3v2 header, assuming we're already 4 bytes within file (file pointer
// being at position byte 3), and return signature after id3
int skip_id3v2() {
	struct id3_hdr_p h;
	_osread(&h, sizeof(h));
	// Synchsafe integers: only bits 0-6 are used (0xxxxxxx 0xxxxxxx)
	// Also if footer present, +20 instead of +10 for size
	int ns = (h.sizea[0] << 21 | h.sizea[1] << 14 |
		h.sizea[2] << 7 | h.sizea[3]) +
		(h.flags & 0x10 ? 20 : 10);
	if (_osseek(ns, SEEK_SET)) goto ID3_END;
	uint32_t s;
	_osread(&s, 4);
	if (check_mp3(s) == 0) {
ID3_END:	report_data();
		exit(0);
	}
	return s;
}

// skip IDv1 header, and return signature after id3
int skip_id3v1() {
	if (_osseek(128, SEEK_SET)) goto ID3_END;
	uint32_t s;
	_osread(&s, 4);
	if (check_mp3(s) == 0) {
ID3_END:	report_data();
		exit(0);
	}
	return s;
}