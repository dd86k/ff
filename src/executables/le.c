#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "le.h"
#include <stdio.h>

/// Scan a LE executable
void scan_le(int is_le) {
	struct e32_hdr h;
	_ddread(&h, sizeof(h));

	char *e, *os, *t, *c, *bo, *wo;

	e = is_le ? "LE" : "LX";

	switch (h.e32_os) {
	case OS2:        os = "OS/2 "; break;
	case Windows:    os = "Windows "; break;
	case DOS4:       os = "DOS 4.x "; break;
	case Windows386: os = "Windows 386 "; break;
	default:         os = "? "; break;
	}

	if (h.e32_mflags & Library) // Compare module flags
		t = "Library"; // Library module
	else if (h.e32_mflags & ProtectedMemoryLibrary)
		t = "Protected Memory Library";
	else if (h.e32_mflags & PhysicalDeviceDriver)
		t = "Physical Device Driver";
	else if (h.e32_mflags & VirtualDeiveDriver)
		t = "Virtual Device Driver";
	else
		t = "Executable"; // Program module

	switch (h.e32_cpu) {
	default:    c = "?"; break;
	case i286:  c = "i286"; break;
	case _i386: c = "i386"; break;
	case i486:  c = "i486"; break;
	}

	bo = h.e32_border ? "BE" : "LE";
	wo = h.e32_worder ? "BE" : "LE";

	reportf("%s %s %s for %s machines, %s byte order, %s word order",
		e, os, t, c, bo, wo);

	if (More) {
		printf(
			"e32_border: %Xh\n"
			"e32_worder: %Xh\n"
			"e32_level : %lXh\n"
			"e32_cpu   : %Xh\n"
			"e32_os    : %Xh\n"
			"e32_ver   : %lXh\n"
			"e32_mflags: %lXh\n",
			h.e32_border,
			h.e32_worder,
			h.e32_level,
			h.e32_cpu,
			h.e32_os,
			h.e32_ver,
			h.e32_mflags
		);
	}
}