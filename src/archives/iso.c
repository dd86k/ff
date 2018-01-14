#include <stdio.h>
#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "iso.h"

// BOOT
char bootsysiden[32];
char bootiden[32];
char bootable;
// PRIMARY_VOL_DESC
char label[31];
char _system[32];
char voliden[128];
char copyright[37];
char publisher[128];
char app[128];
char abst[37];
char biblio[37];
char ctime[23];
char mtime[23];
char etime[23];
char eftime[23];
unsigned long long volume_size;

void scan_block(char *buf) {
	switch (*buf) {
	case BOOT:
		bootable = 1;
		if (More) {
			isoslice(buf + 7, bootsysiden, sizeof(bootsysiden)); // 7..39
			isoslice(buf + 39, bootiden, sizeof(bootiden)); // 39..71
		}
		break;
	case PRIMARY_VOL_DESC:
		isoslice(buf + 40, label, 31); // 40..71
		volume_size = // size * blocksize
			*(unsigned long int*)(&buf[80]) * *(unsigned short*)(&buf[128]);
		if (More) {
			isoslice(buf + 8, _system, sizeof(_system));
			isoslice(buf + 190, voliden, sizeof(voliden)); // 190..318
			isoslice(buf + 318, publisher, sizeof(publisher)); // 318..446
			isoslice(buf + 574, app, sizeof(app)); // 574..702
			isoslice(buf + 702, copyright, sizeof(copyright)); // 702..739
			isoslice(buf + 739, abst, sizeof(abst)); // 739..776
			isoslice(buf + 776, biblio, sizeof(biblio)); // 776..813
			isoslice(buf + 813, ctime, sizeof(ctime)); // 813..830
			isoslice(buf + 830, mtime, sizeof(mtime)); // 830..847
			isoslice(buf + 847, etime, sizeof(etime)); // 847..864
			isoslice(buf + 864, eftime, sizeof(eftime)); // 864..881
		}
		break;
	default: break;
	}
}

// Returns: Returns "true" to stop.
int check_seek(unsigned long int pos, char *buf) {
	if (_ddseek(pos, SEEK_SET)) return 1;
	_ddread(buf, BLOCK_SIZE);
	if (_strcmp_l(buf + 1, ISO, 5) == 0) scan_block(buf);
	return 0;
}

/*string isodate(string stamp) {
	import std.format : format;
	return format("%s-%s-%s %s:%s:%s.%s+%d",
		stamp[0..4], stamp[4..6], stamp[6..8], stamp[8..10],
		stamp[10..12], stamp[12..14], stamp[14..16], stamp[16] * 15);
}*/

void isodate(char *s) {
	//0         10        20
	//2017011318204400# <- #*15
	//2017-01-13 18:20:44.00+3540

	// The middle casting is due to clang's superb implicit casting warning
	*(unsigned short *)(s + 20) = (unsigned short)*(unsigned short *)(s + 14); // ms
	*(unsigned short *)(s + 17) = (unsigned short)*(unsigned short *)(s + 12); // s
	*(unsigned short *)(s + 14) = (unsigned short)*(unsigned short *)(s + 10); // m
	*(unsigned short *)(s + 11) = (unsigned short)*(unsigned short *)(s + 8); // h
	*(unsigned short *)(s + 8)  = (unsigned short)*(unsigned short *)(s + 6); // D
	*(unsigned short *)(s + 5)  = (unsigned short)*(unsigned short *)(s + 4); // M
	s[4] = s[7] = '-';
	s[10] = ' ';
	s[13] = s[16] = ':';
	s[19] = '.';
	s[22] = '\0';
}

// Scan an ISO file
void scan_iso() {
	char buf[BLOCK_SIZE];

	if (check_seek(0x8000, buf)) goto ISO_DONE;
	if (check_seek(0x8800, buf)) goto ISO_DONE;
	if (check_seek(0x9000, buf)) goto ISO_DONE;

ISO_DONE:
	reportn("ISO-9660 CD/DVD disc");
	printf(" \"%s\", ", label);
	_printfd(volume_size);
	if (bootable) printf(", Bootable");

	puts("");

	if (More) {
		isodate(ctime);
		isodate(mtime);
		isodate(etime);
		isodate(eftime);
		printf(
			"Boot System  : %s\n"
			"Boot         : %s\n"
			"System       : %s\n"
			"Volume Set   : %s\n"
			"Publisher    : %s\n"
			"Copyrights   : %s\n"
			"Application  : %s\n"
			"Abstract     : %s\n"
			"Bibliographic: %s\n"
			"Created      : %s\n"
			"Modified     : %s\n"
			"Expires      : %s\n"
			"Effective at : %s\n",
			bootsysiden, bootiden, _system,
			voliden, publisher, copyright,
			app, abst, biblio,
			ctime, mtime, etime, eftime
		);
	}
}