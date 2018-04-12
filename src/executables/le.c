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
    default: printf("? "); break;
    case OS2: printf("OS/2 "); break;
    case Windows: printf("Windows "); break;
    case DOS4: printf("DOS 4.x "); break;
    case Windows386: printf("Windows 386 "); break;
    }

    if (h.e32_mflags & Library)
        printf("Library"); // Library module
    else if (h.e32_mflags & ProtectedMemoryLibrary)
        printf("Protected Memory Library");
    else if (h.e32_mflags & PhysicalDeviceDriver)
        printf("Physical Device Driver");
    else if (h.e32_mflags & VirtualDeiveDriver)
        printf("Virtual Device Driver");
    else
        printf("Executable"); // Program module

    printf(" for ");

    switch (h.e32_cpu) {
    default: printf("?"); break;
    case i286: printf("i286"); break;
    case _i386: printf("i386"); break;
    case i486: printf("i486"); break;
    }

    printf(" machines, ");

    printf(h.e32_border ? "BE" : "LE");
    printf(" Byte order, ");
    printf(h.e32_worder ? "BE" : "LE");
    printf(" Word order");

    puts("");

    if (More) {
        //printf("e32_magic : %s\n", &h.e32_magic[0]);
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
            h.e32_mflags // Module flags
        );
    }
}