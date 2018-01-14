#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "rpm.h"
#include <stdio.h>

void scan_rpm() {
	struct rpm_hdr h;
	_ddread(&h, sizeof(h));
	reportn("RPM ");
	switch (h.type) {
	case 0: printf("binary"); break;
	case 0x100: printf("source"); break;
	default: printf("?"); break;
	}
	printf(" package v%d.%d, \"%s\" for ",
		h.major, h.minor, &h.name[0]);
	switch (h.osnum) {
	case 0x100: printf("linux"); break;
	default: printf("other"); break;
	}
	printf(" platforms\n");
}