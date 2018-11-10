#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "mach.h"
#include <stdio.h>

void scan_mach(uint32_t s) {
	char reversed = 0, fat = 0;

	uint32_t filetype, cpu_type, cpu_subtype, flags;

	char *m, *f, *a;

	switch (s) {
	case MH_MAGIC: m = "32-bit LE "; break;
	case MH_MAGIC_64: m = "64-bit LE "; break;
	case MH_CIGAM: m = "32-bit BE ";
		reversed = 1;
		break;
	case MH_CIGAM_64: m = "64-bit BE ";
		reversed = 1;
		break;
	case FAT_MAGIC: m = "Fat LE ";
		fat = 1;
		break;
	case FAT_CIGAM: m = "Fat BE ";
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
			reportf("Mach-O %s binary file\n", m);
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
	case MH_OBJECT:      f = "Object"; break;
	case MH_EXECUTE:     f = "Executable"; break;
	case MH_FVMLIB:      f = "Fixed VM Library"; break;
	case MH_CORE:        f = "Core"; break;
	case MH_PRELOAD:     f = "Preload"; break;
	case MH_DYLIB:       f = "Dynamic library"; break;
	case MH_DYLINKER:    f = "Dynamic linker"; break;
	case MH_BUNDLE:      f = "Bundle"; break;
	case MH_DYLIB_STUB:  f = "Dynamic library stub"; break;
	case MH_DSYM:        f = "Companion file (debug)"; break;
	case MH_KEXT_BUNDLE: f = "Kext bundle"; break;
	// Fat files have no "filetypes", thus why handled earlier
	default:             f = "?"; break;
	}

	switch (cpu_type) {
	default: a = "?"; break;
	case TYPE_VAX:
		switch (cpu_subtype) {
		case VAX780:  a = "VAX780"; break;
		case VAX785:  a = "VAX785"; break;
		case VAX750:  a = "VAX750"; break;
		case VAX730:  a = "VAX730"; break;
		case UVAXI:   a = "UVAXI"; break;
		case UVAXII:  a = "UVAXII"; break;
		case VAX8200: a = "VAX8200"; break;
		case VAX8500: a = "VAX8500"; break;
		case VAX8600: a = "VAX8600"; break;
		case VAX8650: a = "VAX8650"; break;
		case VAX8800: a = "VAX8800"; break;
		case UVAXIII: a = "UVAXIII"; break;
		default:      a = "VAX"; break;
		}
		break;
	case TYPE_ROMP:
		switch (cpu_subtype) {
		default:     a = "ROMP"; break;
		case RT_PC:  a = "RT_PC"; break;
		case RT_APC: a = "RT_APC"; break;
		case RT_135: a = "RT_135"; break;
		}
		break;
	case TYPE_NS32032: a = "NS32032"; break;
	case TYPE_NS32332: a = "NS32332"; break;
	case TYPE_NS32532:
		a = "NS32532";
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
		case _i386:     a = "i386"; break;
		case i486:      a = "i486"; break;
		case i486SX:    a = "i486SX"; break;
		case i586:      a = "i586"; break;
		case PENPRO:    a = "Pentium Pro"; break;
		case PENTII_M3: a = "Pentium III (M3)"; break;
		case PENTII_M5: a = "Pentium III (M5)"; break;
		case PENTIUM_4: a = "Pentium 4"; break;
		default:        a = "x86"; break;
		}
		break;
	case TYPE_X86_64:
		printl("x86-64");
		break;
	case TYPE_MIPS:
		switch (cpu_subtype) {
		case R2300:  a = "R2300"; break;
		case R2600:  a = "R2600"; break;
		case R2800:  a = "R2800"; break;
		case R2800a: a = "R2800a"; break;
		default:     a = "MIPS"; break;
		}
		break;
	case TYPE_MC680x0:
		switch (cpu_subtype) {
		case MC68030:      a = "MC68030"; break;
		case MC68040:      a = "MC68040"; break;
		case MC68030_ONLY: a = "MC68030 (only)"; break;
		default:           a = "any Motorola 68000"; break;
		}
		break;
	case TYPE_HPPA:
		switch (cpu_subtype) {
		case HPPA7100LC: a = "HPPA7100LC"; break;
		default:         a = "HPPA7100"; break;
		}
		break;
	case TYPE_ARM:
		switch (cpu_subtype) {
		case A500_ARCH: a = "ARM A500"; break;
		case A500:      a = "ARM A500"; break;
		case A440:      a = "ARM A440"; break;
		case M4:        a = "ARM M4"; break;
		case V4T:       a = "ARM V4T"; break;
		case V6:        a = "ARM V6"; break;
		case V5TEJ:     a = "ARM V5TEJ"; break;
		case XSCALE:    a = "ARM XSCALE"; break;
		case V7:        a = "ARM V7"; break;
		default:        a = "ARM"; break;
		}
		break;
	case TYPE_MC88000:
		switch (cpu_subtype) {
		case MC88100: a = "MC88100"; break;
		case MC88110: a = "MC88110"; break;
		default:      a = "M88000"; break;
		}
		break;
	case TYPE_MC98000:
		a = cpu_subtype ? "MC98601" : "MC98000";
		break;
	case TYPE_I860: a = "i860 (MSB)"; break;
	case TYPE_I860_LITTLE: a = "i860 (LSB)"; break;
	case TYPE_RS6000: a = "RS6000"; break;
	case TYPE_POWERPC64:
		switch (cpu_subtype) {
		case POWERPC_601:   a = "PowerPC64 601"; break;
		case POWERPC_602:   a = "PowerPC64 602"; break;
		case POWERPC_603:   a = "PowerPC64 603"; break;
		case POWERPC_603e:  a = "PowerPC64 603e"; break;
		case POWERPC_603ev: a = "PowerPC64 603ev"; break;
		case POWERPC_604:   a = "PowerPC64 604"; break;
		case POWERPC_604e:  a = "PowerPC64 604e"; break;
		case POWERPC_620:   a = "PowerPC64 620"; break;
		case POWERPC_750:   a = "PowerPC64 750"; break;
		case POWERPC_7400:  a = "PowerPC64 7400"; break;
		case POWERPC_7450:  a = "PowerPC64 7450"; break;
		case POWERPC_970:   a = "PowerPC64 970"; break;
		default:            a = "PowerPC64"; break;
		}
	case TYPE_POWERPC:
		switch (cpu_subtype) {
		case POWERPC_601:   a = "PowerPC 601"; break;
		case POWERPC_602:   a = "PowerPC 602"; break;
		case POWERPC_603:   a = "PowerPC 603"; break;
		case POWERPC_603e:  a = "PowerPC 603e"; break;
		case POWERPC_603ev: a = "PowerPC 603ev"; break;
		case POWERPC_604:   a = "PowerPC 604"; break;
		case POWERPC_604e:  a = "PowerPC 604e"; break;
		case POWERPC_620:   a = "PowerPC 620"; break;
		case POWERPC_750:   a = "PowerPC 750"; break;
		case POWERPC_7400:  a = "PowerPC 7400"; break;
		case POWERPC_7450:  a = "PowerPC 7450"; break;
		case POWERPC_970:   a = "PowerPC 970"; break;
		default:            a = "PowerPC"; break;
		}
		break;
	case TYPE_VEO: a = "VEO"; break;
	}

	reportf("Mach-O %s %s for %s", m, f, a);

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

	putchar('\n');
}