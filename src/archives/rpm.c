#include <stdio.h>
#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "rpm.h"

void scan_rpm() {
	struct rpm_hdr h;
	_osread(&h, sizeof(h));

	char *t, *o;

	switch (h.type) {
	case 0: t = "binary"; break;
	case 0x100: t = "source"; break;
	default: t = "type?";
	}
	switch (h.osnum) {
	case 0x100: o = "linux"; break;
	default: o = "other"; break;
	}

	reportf("RPM %s package v%u.%u, \"%.66s\" for %s platforms\n",
		t, h.major, h.minor, h.name, o);
}