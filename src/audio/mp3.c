#include <stdio.h>
#include <stdlib.h>
#include "../ff.h"
#include "../utils.h"
#include "mp3.h"

// MPEG-1 ISO/IEC 11172-3
// MPEG-2 ISO/IEC 13818-3

void scan_mp3(uint32_t sig, int id3) {
	char bv1l1[][8] = {
		"free", "32", "64", "96", "128", "160", "192", "224",
		"256", "288", "320", "352", "384", "416", "448", "bad"
	};
	char bv1l2[][8] = {
		"free", "32", "48", "56", "64", "80", "96", "112",
		"128", "160", "192", "224", "256", "320", "384", "bad"
	};
	char bv1l3[][8] = {
		"free", "32", "40", "48", "56", "64", "80", "96",
		"112", "128", "160", "192", "224", "256", "320", "bad"
	};
	char bv2l1[][8] = {
		"free", "32", "48", "56", "64", "80", "96", "112",
		"128", "144", "160", "176", "192", "224", "256", "bad"
	};
	char bv2l23[][8] = {
		"free", "8", "16", "24", "32", "40", "48", "56",
		"64", "80", "96", "112", "128", "144", "160", "bad"
	};
	char fv1[][8] = {
		"44100", "48000", "32000", "(res.)"
	};
	char fv2[][8] = {
		"22050", "24000", "16000", "(res.)"
	};
	/*char fv25[][8] = {
		"11025", "12000", "8000", "(res.)"
	};*/
	char ca[][8] = {
		"stereo", "joint", "dual", "mono"
	};

	struct mp3_hdr h = *(struct mp3_hdr*)&sig;

	char v = h.sig & 0x80 ? '1' : '2'; /// MPEG version
	char *l; // layer
	char *b; // bitrate
	char *f; // frequency
	char *c; // channels
	size_t bi = h.info >> 4; // bitrate index
	size_t fi = (h.info >> 2) & 3; // frequency index
	size_t ci = (h.extra >> 6); // channel index

	switch (h.sig & 0x600) {
	case 0x200:
		l = "III";
		b = v == '2' ? bv2l23[bi] : bv1l3[bi];
		break;
	case 0x400:
		l = "II";
		b = v == '2' ? bv2l23[bi] : bv1l2[bi];
		break;
	case 0x600:
		l = "I";
		b = v == '2' ? bv2l1[bi] : bv1l1[bi];
		break;
	default:
		l = "(res.)";
		b = "(res.)";
		break;
	}
	f = v == '2' ? fv2[fi] : fv1[fi];
	c = ca[ci];

	reportf(
		"MPEG-%c Audio Layer %s (MP3) audio, %s Hz, %s kbps, %s",
		v, l, f, b, c
	);
	if (ci == 1) {
		if (h.extra & 0x20)
			printf(" +intensity");
		if (h.extra & 0x10)
			printf(" +ms");
	}
	if (id3)
		printf(", id3");
	if (h.sig & 1)
		printf(", crc16");
	if (h.info & 1)
		printf(", priv. bit");
	if (h.info & 2)
		printf(", pad");
	if (h.extra & 8)
		printf(", copyright");
	if (h.extra & 6)
		printf(", original");
	putchar('\n');
}

int check_mp3(uint32_t s) {
	return (bswap16(s) >> 4) == 0xFFF;
}

// skip id3 and return signature
int skip_id3() {
	struct id3_hdr h;
	_ddseek(0, SEEK_SET);
	_ddread(&h, sizeof(h));
	// Synchsafe integers
	// Yep, every 7th bit is not used, on top of being MSB
	// So the entire integer is spread out like so: 0xxxxxxx 0xxxxxxx
	// Also if footer present, +20 instead of +10 for size
	int ns = (h.sizea[0] << 21 | h.sizea[1] << 14 |
		h.sizea[2] << 7 | h.sizea[3]) +
		(h.flags & 0x10 ? 20 : 10);
	if (_ddseek(ns, SEEK_SET)) {
		report_data();
		exit(0);
	}
	uint32_t s;
	_ddread(&s, 4);
	/*if (check_mp3(s)) {
		report_data();
		exit(0);
	}*/
	return s; // don't ask me why
}