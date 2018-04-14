#include <stdio.h>
#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "rpm.h"

void scan_rpm() {
	struct rpm_hdr h;
	_ddread(&h, sizeof(h));
	reportn("RPM ");
	switch (h.type) {
	case 0: printf("binary"); break;
	case 0x100: printf("source"); break;
	default: printf("?");
	}
	printf(" package v%d.%d, \"%.66s\" for ",
		h.major, h.minor, h.name);
	switch (h.osnum) {
	case 0x100: printl("linux"); break;
	default: printl("other"); break;
	}
	puts(" platforms");
}