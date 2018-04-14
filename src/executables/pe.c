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

	reportn("PE32");

	switch (peoh.magic) {
	case ROM: printl("-ROM "); break;
	case HDR32: printl(" "); break;
	case HDR64: printl("+ "); break;
	default: printl("? "); break;
	}

	switch (peoh.Subsystem) {
	case NATIVE:
		printl("Windows Native");
		break;
	case WINDOWS_GUI:
		printl("Windows GUI");
		break;
	case WINDOWS_CUI:
		printl("Windows Console");
		break;
	case POSIX_CUI:
		printl("Posix Console");
		break;
	case WINDOWS_CE_GUI:
		printl("Windows CE GUI");
		break;
	case EFI_APPLICATION :
		printl("EFI");
		break;
	case EFI_BOOT_SERVICE_DRIVER :
		printl("EFI Boot Service driver");
		break;
	case EFI_RUNTIME_DRIVER:
		printl("EFI Runtime driver");
		break;
	case EFI_ROM:
		printl("EFI ROM");
		break;
	case XBOX:
		printl("XBOX");
		break;
	case WINDOWS_BOOT_APPLICATION:
		printl("Windows Boot Application");
		break;
	default:
		printl("?");
		break;
	}

	if (dirs.CLRHeader)
		printl(" .NET");

	if (peh.Characteristics & DLL)
		printl(" Library");
	else if (peh.Characteristics & EXECUTABLE_IMAGE)
		printl(" Executable");
	else
		printl(" ?");

	printl(" for ");

	switch (peh.Machine) {
	default: // UNKNOWN
		printl("?");
		break;
	case I386:
		printl("x86");
		break;
	case AMD64:
		printl("x86-64");
		break;
	case IA64:
		printl("IA64");
		break;
	case EBC:
		printl("EFI (Byte Code)");
		break;
	case CLR:
		printl("Common Language Runtime");
		break;
	case ARM:
		printl("ARM (Little Endian)");
		break;
	case ARMNT:
		printl("ARMv7+ (Thumb)");
		break;
	case ARM64:
		printl("ARMv8 (64-bit)");
		break;
	case M32R:
		printl("Mitsubishi M32R (Little endian)");
		break;
	case AM33:
		printl("Matsushita AM33");
		break;
	case MIPS16:
		printl("MIPS16");
		break;
	case MIPSFPU:
		printl("MIPS (w/FPU)");
		break;
	case MIPSFPU16:
		printl("MIPS16 (w/FPU)");
		break;
	case POWERPC:
		printl("PowerPC");
		break;
	case POWERPCFP:
		printl("PowerPC (w/FPU)");
		break;
	case R4000:
		printl("MIPS (Little endian)");
		break;
	case SH3:
		printl("Hitachi SH3");
		break;
	case SH3DSP:
		printl("Hitachi SH3 DSP");
		break;
	case SH4:
		printl("Hitachi SH4");
		break;
	case SH5:
		printl("Hitachi SH5");
		break;
	case THUMB:
		printl("ARM or Thumb (\"Interworking\")");
		break;
	case WCEMIPSV2:
		printl("MIPS WCE v2 (Little Endian)");
		break;
	}

	printl(" machines");

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

	printl("\n");

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