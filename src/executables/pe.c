#include "../utils.h"
#include "../settings.h"
#include "pe.h"
#include <stdio.h>

void scan_pe() {
	struct PE_HEADER peh; // PE32
	struct PE_OPTIONAL_HEADER peoh;
	struct IMAGE_DATA_DIRECTORY dirs;

	_ddread(&peh, sizeof(peh));

	if (peh.SizeOfOptionalHeader) { // PE Optional Header
		_ddread(&peoh, sizeof(peoh));
		if (peoh.magic == HDR64) // PE_FORMAT
			_ddseek(16, SEEK_CUR);
		_ddread(&dirs, sizeof(dirs));
	}

	char *p, *s, *net, *c, *m;

	switch (peoh.magic) {
	case ROM:   p = "-ROM"; break;
	case HDR32: p = ""; break;
	case HDR64: p = "+"; break;
	default:    p = "?"; break;
	}

	switch (peoh.Subsystem) {
	case NATIVE:                   s = "Windows Native"; break;
	case WINDOWS_GUI:              s = "Windows GUI"; break;
	case WINDOWS_CUI:              s = "Windows Console"; break;
	case POSIX_CUI:                s = "Posix Console"; break;
	case WINDOWS_CE_GUI:           s = "Windows CE GUI"; break;
	case EFI_APPLICATION:          s = "EFI"; break;
	case EFI_BOOT_SERVICE_DRIVER:  s = "EFI Boot Service driver"; break;
	case EFI_RUNTIME_DRIVER:       s = "EFI Runtime driver"; break;
	case EFI_ROM:                  s = "EFI ROM"; break;
	case XBOX:                     s = "XBOX"; break;
	case WINDOWS_BOOT_APPLICATION: s = "Windows Boot Application"; break;
	default: s = "?"; break;
	}

	net = dirs.CLRHeader ? ".NET " : "";

	if (peh.Characteristics & DLL)
		c = "Library";
	else if (peh.Characteristics & EXECUTABLE_IMAGE)
		c = "Executable";
	else
		c = "?";

	switch (peh.Machine) {
	case I386:      m = "x86"; break;
	case AMD64:     m = "x86-64"; break;
	case IA64:      m = "IA64"; break;
	case EBC:       m = "EFI (bytecode)"; break;
	case CLR:       m = "Common Language Runtime"; break;
	case ARM:       m = "ARM (LE)"; break;
	case ARMNT:     m = "ARMv7+ (Thumb)"; break;
	case ARM64:     m = "ARMv8 (64-bit)"; break;
	case M32R:      m = "Mitsubishi M32R (LE)"; break;
	case AM33:      m = "Matsushita AM33"; break;
	case MIPS16:    m = "MIPS16"; break;
	case MIPSFPU:   m = "MIPS (+FPU)"; break;
	case MIPSFPU16: m = "MIPS16 (+FPU)"; break;
	case POWERPC:   m = "PowerPC"; break;
	case POWERPCFP: m = "PowerPC (+FPU)"; break;
	case R4000:     m = "MIPS (LE)"; break;
	case SH3:       m = "Hitachi SH3"; break;
	case SH3DSP:    m = "Hitachi SH3 DSP"; break;
	case SH4:       m = "Hitachi SH4"; break;
	case SH5:       m = "Hitachi SH5"; break;
	case THUMB:     m = "ARM/Thumb (\"Interworking\")"; break;
	case WCEMIPSV2: m = "MIPS WCE v2 (LE)"; break;
	default:        m = "?"; break;
	}

	reportf("PE32%s %s %s%s for %s", p, s, net, c, m);

	if (peh.Characteristics) {
		if (peh.Characteristics & RELOCS_STRIPPED)
			printl(", RELOCS_STRIPPED");
		if (peh.Characteristics & LINE_NUMS_STRIPPED)
			printl(", LINE_NUMS_STRIPPED");
		if (peh.Characteristics & LOCAL_SYMS_STRIPPED)
			printl(", LOCAL_SYMS_STRIPPED");
		if (peh.Characteristics & LARGE_ADDRESS_AWARE)
			printl(", LARGE_ADDRESS_AWARE");
		if (peh.Characteristics & _16BIT_MACHINE)
			printl(", 16BIT_MACHINE");
		if (peh.Characteristics & _32BIT_MACHINE)
			printl(", 32BIT_MACHINE");
		if (peh.Characteristics & DEBUG_STRIPPED)
			printl(", DEBUG_STRIPPED");
		if (peh.Characteristics & REMOVABLE_RUN_FROM_SWAP)
			printl(", REMOVABLE_RUN_FROM_SWAP");
		if (peh.Characteristics & NET_RUN_FROM_SWAP)
			printl(", NET_RUN_FROM_SWAP");
		if (peh.Characteristics & SYSTEM)
			printl(", SYSTEM");
		if (peh.Characteristics & UP_SYSTEM_ONLY)
			printl(", UP_SYSTEM_ONLY");
	}

	putchar('\n');

	if (More) {
		printf(
			"Number of sections     : %Xh\n"
			"Timestamp              : %Xh\n"
			"Pointer to Symbol Table: %Xh\n"
			"Number of symbols      : %Xh\n"
			"Size of Optional Header: %Xh\n"
			"Characteristics        : %Xh\n",
			peh.NumberOfSymbols,
			peh.TimeDateStamp,
			peh.PointerToSymbolTable,
			peh.NumberOfSymbols,
			peh.SizeOfOptionalHeader,
			peh.Characteristics
		);
	}
}