#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "le.h"
#include <stdio.h>

/// Scan a LE executable
void scan_le(int is_le) {
    struct e32_hdr h;
    _ddread(&h, sizeof(h));

	reportn(is_le ? "LE " : "LX ");

    switch (h.e32_os) {
    default: printl("? "); break;
    case OS2: printl("OS/2 "); break;
    case Windows: printl("Windows "); break;
    case DOS4: printl("DOS 4.x "); break;
    case Windows386: printl("Windows 386 "); break;
    }

    if (h.e32_mflags & Library) // Compare module flags
        printl("Library"); // Library module
    else if (h.e32_mflags & ProtectedMemoryLibrary)
        printl("Protected Memory Library");
    else if (h.e32_mflags & PhysicalDeviceDriver)
        printl("Physical Device Driver");
    else if (h.e32_mflags & VirtualDeiveDriver)
        printl("Virtual Device Driver");
    else
        printl("Executable"); // Program module

    printl(" for ");

    switch (h.e32_cpu) {
    default: printl("?"); break;
    case i286: printl("i286"); break;
    case _i386: printl("i386"); break;
    case i486: printl("i486"); break;
    }

    printl(" machines, ");

    printl(h.e32_border ? "BE" : "LE");
    printl(" Byte order, ");
    printl(h.e32_worder ? "BE" : "LE");
    puts(" Word order");

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