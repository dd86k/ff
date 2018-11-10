#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "elf.h"
#include <stdio.h>

/// Scan an ELF image
void scan_elf() {
	struct Elf32_Ehdr h;
	_ddread(&h, sizeof(h));

	char *c = elf_class(h.e_ident[EI_CLASS-4]);
	char *d = elf_data(h.e_ident[EI_DATA-4]);
	char *a = elf_osabi(h.e_ident[EI_OSABI-4]);
	char *t = elf_type(h.e_type);
	char *m = elf_machine(h.e_machine);

	reportf("ELF%s%s %s %s for %s machines\n", c, d, a, t, m);
}

// These functions below are also used by FatELF

char* elf_class(uint8_t c) {
	switch (c) {
	case 1:  return "32";
	case 2:  return "64";
	default: return "?";
	}
}

char* elf_data(uint8_t c) {
	switch (c) {
	case 1:  return "LE";
	case 2:  return "BE";
	default: return "?";
	}
}

char* elf_osabi(uint8_t c) {
	switch (c) {
	default:   return "DECL?";
	case 0x00: return "System V";
	case 0x01: return "HP-UX";
	case 0x02: return "NetBSD";
	case 0x03: return "Linux";
	case 0x06: return "Solaris";
	case 0x07: return "AIX";
	case 0x08: return "IRIX";
	case 0x09: return "FreeBSD";
	case 0x0C: return "OpenBSD";
	case 0x0D: return "OpenVMS";
	case 0x0E: return "NonStop Kernel";
	case 0x0F: return "AROS";
	case 0x10: return "Fenix OS";
	case 0x11: return "CloudABI";
	case 0x53: return "Sortix";
	}
}

char* elf_type(uint16_t c) {
	switch (c) {
	default:        return "?";
	case ET_NONE:   return "(No file type)";
	case ET_REL:    return "Relocatable";
	case ET_EXEC:   return "Executable";
	case ET_DYN:    return "Shared object";
	case ET_CORE:   return "Core";
	case ET_LOPROC: return "Professor-specific (LO)";
	case ET_HIPROC: return "Professor-specific (HI)";
	}
}

char* elf_machine(uint16_t c) {
	switch (c) {
	case EM_NONE:    return "no";
	case EM_M32:     return "AT&T WE 32100 (M32)";
	case EM_SPARC:   return "SPARC";
	case EM_860:     return "Intel 80860";
	case EM_386:     return "x86";
	case EM_IA64:    return "IA64";
	case EM_AMD64:   return "x86-64";
	case EM_68K:     return "Motorola 68000";
	case EM_88K:     return "Motorola 88000";
	case EM_MIPS:    return "MIPS RS3000";
	case EM_POWERPC: return "PowerPC";
	case EM_ARM:     return "ARM";
	case EM_SUPERH:  return "SuperH";
	case EM_AARCH64: return "ARM (64-bit)";
	default:         return "machine?";
	}
}