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
		printf("32-bit LE ");
		break;
	case MH_MAGIC_64:
		printf("64-bit LE ");
		break;
	case MH_CIGAM:
		printf("32-bit BE ");
		reversed = 1;
		break;
	case MH_CIGAM_64:
		printf("64-bit BE ");
		reversed = 1;
		break;
	case FAT_MAGIC:
		printf("Fat LE ");
		fat = 1;
		break;
	case FAT_CIGAM:
		printf("Fat BE ");
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
		printf("?");
		break;
	case MH_OBJECT:
		printf("Object");
		break;
	case MH_EXECUTE:
		printf("Executable");
		break;
	case MH_FVMLIB:
		printf("Fixed VM Library");
		break;
	case MH_CORE:
		printf("Core");
		break;
	case MH_PRELOAD:
		printf("Preload");
		break;
	case MH_DYLIB:
		printf("Dynamic library");
		break;
	case MH_DYLINKER:
		printf("Dynamic linker");
		break;
	case MH_BUNDLE:
		printf("Bundle");
		break;
	case MH_DYLIB_STUB:
		printf("Dynamic library stub");
		break;
	case MH_DSYM:
		printf("Companion file (debug)");
		break;
	case MH_KEXT_BUNDLE:
		printf("Kext bundle");
		break;
	}

	printf(" for ");

	switch (cpu_type) {
	default: printf("?"); break;
	case TYPE_VAX:
		switch (cpu_subtype) {
		default: printf("VAX"); break;
		case VAX780: printf("VAX780"); break;
		case VAX785: printf("VAX785"); break;
		case VAX750: printf("VAX750"); break;
		case VAX730: printf("VAX730"); break;
		case UVAXI: printf("UVAXI"); break;
		case UVAXII: printf("UVAXII"); break;
		case VAX8200: printf("VAX8200"); break;
		case VAX8500: printf("VAX8500"); break;
		case VAX8600: printf("VAX8600"); break;
		case VAX8650: printf("VAX8650"); break;
		case VAX8800: printf("VAX8800"); break;
		case UVAXIII: printf("UVAXIII"); break;
		}
		break;
	case TYPE_ROMP:
		switch (cpu_subtype) {
		default: printf("ROMP"); break;
		case RT_PC: printf("RT_PC"); break;
		case RT_APC: printf("RT_APC"); break;
		case RT_135: printf("RT_135"); break;
		}
		break;
	case TYPE_NS32032:
		printf("NS32032");
		break;
	case TYPE_NS32332:
		printf("NS32332");
		break;
	case TYPE_NS32532:
		printf("NS32532");
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
		default: printf("any x86"); break;
		case i386: printf("i386"); break;
		case i486: printf("i486"); break;
		case i486SX: printf("i486SX"); break;
		case i586: printf("i586"); break;
		case PENPRO: printf("Pentium Pro"); break;
		case PENTII_M3: printf("Pentium III (M3)"); break;
		case PENTII_M5: printf("Pentium III (M5)"); break;
		case PENTIUM_4: printf("Pentium 4"); break;
		}
		break;
	case TYPE_X86_64:
		printf("any x86-64");
		break;
	case TYPE_MIPS:
		switch (cpu_subtype) {
		default: printf("any MIPS"); break;
		case R2300: printf("R2300"); break;
		case R2600: printf("R2600"); break;
		case R2800: printf("R2800"); break;
		case R2800a: printf("R2800a"); break;
		}
		break;
	case TYPE_MC680x0:
		switch (cpu_subtype) {
		default: printf("any Motorola 68000"); break;
		case MC68030: printf("MC68030"); break;
		case MC68040: printf("MC68040"); break;
		case MC68030_ONLY: printf("MC68030 (only)"); break;
		}
		break;
	case TYPE_HPPA:
		switch (cpu_subtype) {
		default: printf("HPPA7100"); break;
		case HPPA7100LC: printf("HPPA7100LC"); break;
		}
		break;
	case TYPE_ARM:
		if (cpu_subtype) {
			printf("ARM ");
			switch (cpu_subtype) {
			case A500_ARCH: printf("A500 Arch"); break;
			case A500: printf("A500"); break;
			case A440: printf("A440"); break;
			case M4: printf("M4"); break;
			case V4T: printf("V4T"); break;
			case V6: printf("V6"); break;
			case V5TEJ: printf("V5TEJ"); break;
			case XSCALE: printf("XSCALE"); break;
			case V7: printf("V7"); break;
			}
		} else printf("any ARM");
		break;
	case TYPE_MC88000:
		switch (cpu_subtype) {
		default: printf("any Motorola 88000"); break;
		case MC88100: printf("MC88100"); break;
		case MC88110: printf("MC88110"); break;
		}
		break;
	case TYPE_MC98000:
		if (cpu_subtype)
			printf("MC98601");
		else
			printf("MC98000");
		break;
	case TYPE_I860:
		if (cpu_subtype) printf("any i860 (MSB)");
		else printf("any i860 (MSB)");
		break;
	case TYPE_I860_LITTLE:
		if (cpu_subtype) printf("any i860 (LSB)");
		else printf("any i860 (LSB)");
		break;
	case TYPE_RS6000:
		printf("RS6000");
		break;
	case TYPE_POWERPC64:
	case TYPE_POWERPC:
		printf("PowerPC");
		if (TYPE_POWERPC64) printf("64");
		switch (cpu_subtype) {
		case POWERPC_601: printf(" 601"); break;
		case POWERPC_602: printf(" 602"); break;
		case POWERPC_603: printf(" 603"); break;
		case POWERPC_603e: printf(" 603e"); break;
		case POWERPC_603ev: printf(" 603ev"); break;
		case POWERPC_604: printf(" 604"); break;
		case POWERPC_604e: printf(" 604e"); break;
		case POWERPC_620: printf(" 620"); break;
		case POWERPC_750: printf(" 750"); break;
		case POWERPC_7400: printf(" 7400"); break;
		case POWERPC_7450: printf(" 7450"); break;
		case POWERPC_970: printf(" 970"); break;
		default: break;
		}
		break;
	case TYPE_VEO:
		printf("any VEO");
		break;
	}

	printf(" processors");

	if (flags) {
		if (flags & MH_NOUNDEFS)
			printf(", MH_NOUNDEFS");
		if (flags & MH_INCRLINK)
			printf(", MH_INCRLINK");
		if (flags & MH_DYLDLINK)
			printf(", MH_DYLDLINK");
		if (flags & MH_BINDATLOAD)
			printf(", MH_BINDATLOAD");
		if (flags & MH_PREBOUND)
			printf(", MH_PREBOUND");
		if (flags & MH_SPLIT_SEGS)
			printf(", MH_SPLIT_SEGS");
		if (flags & MH_LAZY_INIT)
			printf(", MH_LAZY_INIT");
		if (flags & MH_TWOLEVEL)
			printf(", MH_TWOLEVEL");
		if (flags & MH_FORCE_FLAT)
			printf(", MH_FORCE_FLAT");
		if (flags & MH_NOMULTIDEFS)
			printf(", MH_NOMULTIDEFS");
		if (flags & MH_NOFIXPREBINDING)
			printf(", MH_NOFIXPREBINDING");
		if (flags & MH_PREBINDABLE)
			printf(", MH_PREBINDABLE");
		if (flags & MH_ALLMODSBOUND)
			printf(", MH_ALLMODSBOUND");
		if (flags & MH_SUBSECTIONS_VIA_SYMBOLS)
			printf(", MH_SUBSECTIONS_VIA_SYMBOLS");
		if (flags & MH_CANONICAL)
			printf(", MH_CANONICAL");
		if (flags & MH_WEAK_DEFINES)
			printf(", MH_WEAK_DEFINES");
		if (flags & MH_BINDS_TO_WEAK)
			printf(", MH_BINDS_TO_WEAK");
		if (flags & MH_ALLOW_STACK_EXECUTION)
			printf(", MH_ALLOW_STACK_EXECUTION");
		if (flags & MH_ROOT_SAFE)
			printf(", MH_ROOT_SAFE");
		if (flags & MH_SETUID_SAFE)
			printf(", MH_SETUID_SAFE");
		if (flags & MH_NO_REEXPORTED_DYLIBS)
			printf(", MH_NO_REEXPORTED_DYLIBS");
		if (flags & MH_PIE)
			printf(", MH_PIE");
		if (flags & MH_DEAD_STRIPPABLE_DYLIB)
			printf(", MH_DEAD_STRIPPABLE_DYLIB");
		if (flags & MH_HAS_TLV_DESCRIPTORS)
			printf(", MH_HAS_TLV_DESCRIPTORS");
		if (flags & MH_NO_HEAP_EXECUTION)
			printf(", MH_NO_HEAP_EXECUTION");
		if (flags & MH_APP_EXTENSION_SAFE)
			printf(", MH_APP_EXTENSION_SAFE");
	}

	puts("");
}