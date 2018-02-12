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
			_ddseek(16, SEEK_CUR); //fseek(fp, 16, SEEK_CUR);
		_ddread(&dirs, sizeof(dirs));
	}

	reportn("PE32");

	switch (peoh.magic) {
	case ROM: printf("-ROM "); break;
	case HDR32: printf(" "); break;
	case HDR64: printf("+ "); break;
	default: printf("? "); break;
	}

	switch (peoh.Subsystem) {
	case NATIVE:
		printf("Windows Native");
		break;
	case WINDOWS_GUI:
		printf("Windows GUI");
		break;
	case WINDOWS_CUI:
		printf("Windows Console");
		break;
	case POSIX_CUI:
		printf("Posix Console");
		break;
	case WINDOWS_CE_GUI:
		printf("Windows CE GUI");
		break;
	case EFI_APPLICATION :
		printf("EFI");
		break;
	case EFI_BOOT_SERVICE_DRIVER :
		printf("EFI Boot Service driver");
		break;
	case EFI_RUNTIME_DRIVER:
		printf("EFI Runtime driver");
		break;
	case EFI_ROM:
		printf("EFI ROM");
		break;
	case XBOX:
		printf("XBOX");
		break;
	case WINDOWS_BOOT_APPLICATION:
		printf("Windows Boot Application");
		break;
	default:
		printf("?");
		break;
	}

	if (dirs.CLRHeader)
		printf(" .NET");

	if (peh.Characteristics & DLL)
		printf(" Library");
	else if (peh.Characteristics & EXECUTABLE_IMAGE)
		printf(" Executable");
	else
		printf(" ?");

	printf(" for ");

	switch (peh.Machine) {
	default: // UNKNOWN
		printf("?");
		break;
	case I386:
		printf("x86");
		break;
	case AMD64:
		printf("x86-64");
		break;
	case IA64:
		printf("IA64");
		break;
	case EBC:
		printf("EFI (Byte Code)");
		break;
	case CLR:
		printf("Common Language Runtime");
		break;
	case ARM:
		printf("ARM (Little Endian)");
		break;
	case ARMNT:
		printf("ARMv7+ (Thumb)");
		break;
	case ARM64:
		printf("ARMv8 (64-bit)");
		break;
	case M32R:
		printf("Mitsubishi M32R (Little endian)");
		break;
	case AM33:
		printf("Matsushita AM33");
		break;
	case MIPS16:
		printf("MIPS16");
		break;
	case MIPSFPU:
		printf("MIPS (w/FPU)");
		break;
	case MIPSFPU16:
		printf("MIPS16 (w/FPU)");
		break;
	case POWERPC:
		printf("PowerPC");
		break;
	case POWERPCFP:
		printf("PowerPC (w/FPU)");
		break;
	case R4000:
		printf("MIPS (Little endian)");
		break;
	case SH3:
		printf("Hitachi SH3");
		break;
	case SH3DSP:
		printf("Hitachi SH3 DSP");
		break;
	case SH4:
		printf("Hitachi SH4");
		break;
	case SH5:
		printf("Hitachi SH5");
		break;
	case THUMB:
		printf("ARM or Thumb (\"Interworking\")");
		break;
	case WCEMIPSV2:
		printf("MIPS WCE v2 (Little Endian)");
		break;
	}

	printf(" machines");

	if (peh.Characteristics) {
		if (peh.Characteristics & RELOCS_STRIPPED)
			printf(", RELOCS_STRIPPED");
		if (peh.Characteristics & LINE_NUMS_STRIPPED)
			printf(", LINE_NUMS_STRIPPED");
		if (peh.Characteristics & LOCAL_SYMS_STRIPPED)
			printf(", LOCAL_SYMS_STRIPPED");
		if (peh.Characteristics & LARGE_ADDRESS_AWARE)
			printf(", LARGE_ADDRESS_AWARE");
		if (peh.Characteristics & _16BIT_MACHINE)
			printf(", 16BIT_MACHINE");
		if (peh.Characteristics & _32BIT_MACHINE)
			printf(", 32BIT_MACHINE");
		if (peh.Characteristics & DEBUG_STRIPPED)
			printf(", DEBUG_STRIPPED");
		if (peh.Characteristics & REMOVABLE_RUN_FROM_SWAP)
			printf(", REMOVABLE_RUN_FROM_SWAP");
		if (peh.Characteristics & NET_RUN_FROM_SWAP)
			printf(", NET_RUN_FROM_SWAP");
		if (peh.Characteristics & SYSTEM)
			printf(", SYSTEM");
		if (peh.Characteristics & UP_SYSTEM_ONLY)
			printf(", UP_SYSTEM_ONLY");
	}

	puts("");

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