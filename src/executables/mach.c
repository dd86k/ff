#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "mach.h"
#include <stdio.h>

void scan_mach(uint32_t s) {
	char reversed = 0;
	char fat = 0;

	uint32_t filetype;
	uint32_t cpu_type;
	uint32_t cpu_subtype;
	uint32_t flags;

	reportn("Mach-O ");

	switch (s) {
	case MH_MAGIC:
		printl("32-bit LE ");
		break;
	case MH_MAGIC_64:
		printl("64-bit LE ");
		break;
	case MH_CIGAM:
		printl("32-bit BE ");
		reversed = 1;
		break;
	case MH_CIGAM_64:
		printl("64-bit BE ");
		reversed = 1;
		break;
	case FAT_MAGIC:
		printl("Fat LE ");
		fat = 1;
		break;
	case FAT_CIGAM:
		printl("Fat BE ");
		reversed = 1; fat = 1;
		break;
	}

	if (fat) { // Java prefers Fat files
		struct fatmach_header fh;
		_ddread(&fh, sizeof(fh));

		if (fh.nfat_arch) {
			struct fat_arch fa;
			_ddread(&fa, sizeof(fa));

			if (reversed) {
				cpu_type = bswap32(fa.cputype);
				cpu_subtype = bswap32(fa.cpusubtype);
			} else {
				cpu_type = fa.cputype;
				cpu_subtype = fa.cpusubtype;
			}
		} else {
			puts("binary file");
			return;
		}
	} else {
		struct mach_header mh;
		_ddread(&mh, sizeof(mh));

		if (reversed) {
			filetype = bswap32(mh.filetype);
			cpu_type = bswap32(mh.cputype);
			cpu_subtype = bswap32(mh.cpusubtype);
		} else {
			filetype = mh.filetype;
			cpu_type = mh.cputype;
			cpu_subtype = mh.cpusubtype;
		}
		flags = mh.flags;
	}

	switch (filetype) {
	default: // Fat files have no "filetypes".
		printl("?");
		break;
	case MH_OBJECT:
		printl("Object");
		break;
	case MH_EXECUTE:
		printl("Executable");
		break;
	case MH_FVMLIB:
		printl("Fixed VM Library");
		break;
	case MH_CORE:
		printl("Core");
		break;
	case MH_PRELOAD:
		printl("Preload");
		break;
	case MH_DYLIB:
		printl("Dynamic library");
		break;
	case MH_DYLINKER:
		printl("Dynamic linker");
		break;
	case MH_BUNDLE:
		printl("Bundle");
		break;
	case MH_DYLIB_STUB:
		printl("Dynamic library stub");
		break;
	case MH_DSYM:
		printl("Companion file (debug)");
		break;
	case MH_KEXT_BUNDLE:
		printl("Kext bundle");
		break;
	}

	printl(" for ");

	switch (cpu_type) {
	default: printl("?"); break;
	case TYPE_VAX:
		switch (cpu_subtype) {
		default: printl("VAX"); break;
		case VAX780: printl("VAX780"); break;
		case VAX785: printl("VAX785"); break;
		case VAX750: printl("VAX750"); break;
		case VAX730: printl("VAX730"); break;
		case UVAXI: printl("UVAXI"); break;
		case UVAXII: printl("UVAXII"); break;
		case VAX8200: printl("VAX8200"); break;
		case VAX8500: printl("VAX8500"); break;
		case VAX8600: printl("VAX8600"); break;
		case VAX8650: printl("VAX8650"); break;
		case VAX8800: printl("VAX8800"); break;
		case UVAXIII: printl("UVAXIII"); break;
		}
		break;
	case TYPE_ROMP:
		switch (cpu_subtype) {
		default: printl("ROMP"); break;
		case RT_PC: printl("RT_PC"); break;
		case RT_APC: printl("RT_APC"); break;
		case RT_135: printl("RT_135"); break;
		}
		break;
	case TYPE_NS32032:
		printl("NS32032");
		break;
	case TYPE_NS32332:
		printl("NS32332");
		break;
	case TYPE_NS32532:
		printl("NS32532");
		/*switch (cpu_subtype) { aaaand don't feel like it
MMAX_DPC
SQT
MMAX_APC_FPU
MMAX_APC_FPA
MMAX_XPC
		}*/
		break;
	case TYPE_I386:
		switch (cpu_subtype) {
		default: printl("any x86"); break;
		case _i386: printl("i386"); break;
		case i486: printl("i486"); break;
		case i486SX: printl("i486SX"); break;
		case i586: printl("i586"); break;
		case PENPRO: printl("Pentium Pro"); break;
		case PENTII_M3: printl("Pentium III (M3)"); break;
		case PENTII_M5: printl("Pentium III (M5)"); break;
		case PENTIUM_4: printl("Pentium 4"); break;
		}
		break;
	case TYPE_X86_64:
		printl("any x86-64");
		break;
	case TYPE_MIPS:
		switch (cpu_subtype) {
		default: printl("any MIPS"); break;
		case R2300: printl("R2300"); break;
		case R2600: printl("R2600"); break;
		case R2800: printl("R2800"); break;
		case R2800a: printl("R2800a"); break;
		}
		break;
	case TYPE_MC680x0:
		switch (cpu_subtype) {
		default: printl("any Motorola 68000"); break;
		case MC68030: printl("MC68030"); break;
		case MC68040: printl("MC68040"); break;
		case MC68030_ONLY: printl("MC68030 (only)"); break;
		}
		break;
	case TYPE_HPPA:
		switch (cpu_subtype) {
		default: printl("HPPA7100"); break;
		case HPPA7100LC: printl("HPPA7100LC"); break;
		}
		break;
	case TYPE_ARM:
		if (cpu_subtype) {
			printl("ARM ");
			switch (cpu_subtype) {
			case A500_ARCH: printl("A500 Arch"); break;
			case A500: printl("A500"); break;
			case A440: printl("A440"); break;
			case M4: printl("M4"); break;
			case V4T: printl("V4T"); break;
			case V6: printl("V6"); break;
			case V5TEJ: printl("V5TEJ"); break;
			case XSCALE: printl("XSCALE"); break;
			case V7: printl("V7"); break;
			}
		} else printl("any ARM");
		break;
	case TYPE_MC88000:
		switch (cpu_subtype) {
		default: printl("any Motorola 88000"); break;
		case MC88100: printl("MC88100"); break;
		case MC88110: printl("MC88110"); break;
		}
		break;
	case TYPE_MC98000:
		if (cpu_subtype)
			printl("MC98601");
		else
			printl("MC98000");
		break;
	case TYPE_I860:
		if (cpu_subtype) printl("any i860 (MSB)");
		else printl("any i860 (MSB)");
		break;
	case TYPE_I860_LITTLE:
		if (cpu_subtype) printl("any i860 (LSB)");
		else printl("any i860 (LSB)");
		break;
	case TYPE_RS6000:
		printl("RS6000");
		break;
	case TYPE_POWERPC64:
	case TYPE_POWERPC:
		printl("PowerPC");
		if (TYPE_POWERPC64) printl("64");
		switch (cpu_subtype) {
		case POWERPC_601: printl(" 601"); break;
		case POWERPC_602: printl(" 602"); break;
		case POWERPC_603: printl(" 603"); break;
		case POWERPC_603e: printl(" 603e"); break;
		case POWERPC_603ev: printl(" 603ev"); break;
		case POWERPC_604: printl(" 604"); break;
		case POWERPC_604e: printl(" 604e"); break;
		case POWERPC_620: printl(" 620"); break;
		case POWERPC_750: printl(" 750"); break;
		case POWERPC_7400: printl(" 7400"); break;
		case POWERPC_7450: printl(" 7450"); break;
		case POWERPC_970: printl(" 970"); break;
		default: break;
		}
		break;
	case TYPE_VEO:
		printl("any VEO");
		break;
	}

	printl(" processors");

	if (flags) {
		if (flags & MH_NOUNDEFS)
			printl(", MH_NOUNDEFS");
		if (flags & MH_INCRLINK)
			printl(", MH_INCRLINK");
		if (flags & MH_DYLDLINK)
			printl(", MH_DYLDLINK");
		if (flags & MH_BINDATLOAD)
			printl(", MH_BINDATLOAD");
		if (flags & MH_PREBOUND)
			printl(", MH_PREBOUND");
		if (flags & MH_SPLIT_SEGS)
			printl(", MH_SPLIT_SEGS");
		if (flags & MH_LAZY_INIT)
			printl(", MH_LAZY_INIT");
		if (flags & MH_TWOLEVEL)
			printl(", MH_TWOLEVEL");
		if (flags & MH_FORCE_FLAT)
			printl(", MH_FORCE_FLAT");
		if (flags & MH_NOMULTIDEFS)
			printl(", MH_NOMULTIDEFS");
		if (flags & MH_NOFIXPREBINDING)
			printl(", MH_NOFIXPREBINDING");
		if (flags & MH_PREBINDABLE)
			printl(", MH_PREBINDABLE");
		if (flags & MH_ALLMODSBOUND)
			printl(", MH_ALLMODSBOUND");
		if (flags & MH_SUBSECTIONS_VIA_SYMBOLS)
			printl(", MH_SUBSECTIONS_VIA_SYMBOLS");
		if (flags & MH_CANONICAL)
			printl(", MH_CANONICAL");
		if (flags & MH_WEAK_DEFINES)
			printl(", MH_WEAK_DEFINES");
		if (flags & MH_BINDS_TO_WEAK)
			printl(", MH_BINDS_TO_WEAK");
		if (flags & MH_ALLOW_STACK_EXECUTION)
			printl(", MH_ALLOW_STACK_EXECUTION");
		if (flags & MH_ROOT_SAFE)
			printl(", MH_ROOT_SAFE");
		if (flags & MH_SETUID_SAFE)
			printl(", MH_SETUID_SAFE");
		if (flags & MH_NO_REEXPORTED_DYLIBS)
			printl(", MH_NO_REEXPORTED_DYLIBS");
		if (flags & MH_PIE)
			printl(", MH_PIE");
		if (flags & MH_DEAD_STRIPPABLE_DYLIB)
			printl(", MH_DEAD_STRIPPABLE_DYLIB");
		if (flags & MH_HAS_TLV_DESCRIPTORS)
			printl(", MH_HAS_TLV_DESCRIPTORS");
		if (flags & MH_NO_HEAP_EXECUTION)
			printl(", MH_NO_HEAP_EXECUTION");
		if (flags & MH_APP_EXTENSION_SAFE)
			printl(", MH_APP_EXTENSION_SAFE");
	}

	printl("\n");
}