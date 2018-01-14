#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "elf.h"
#include <stdio.h>

/// Scan an ELF image
void scan_elf() {
    struct Elf32_Ehdr h;
    _ddread(&h, sizeof(h));

    reportn("ELF");
    elf_print_class(h.e_ident[EI_CLASS-4]);
    elf_print_data(h.e_ident[EI_DATA-4]);
    elf_print_osabi(h.e_ident[EI_OSABI-4]);
    printf(" ");
    elf_print_type(h.e_type);
    printf(" for ");
    elf_print_machine(h.e_machine);
    printf(" machines\n");

    if (More) {
        printf(
            "e_type     : %X\n"
            "e_machine  : %X\n"
            "e_version  : %X\n"
            "e_entry    : %X\n"
            "e_phoff    : %X\n"
            "e_shoff    : %X\n"
            "e_flags    : %X\n"
            "e_ehsize   : %X\n"
            "e_phentsize: %X\n"
            "e_phnum    : %X\n"
            "e_shentsize: %X\n"
            "e_shnum    : %X\n"
            "e_shstrndx : %X\n",
            h.e_type, h.e_machine, h.e_version,
            h.e_entry, h.e_phoff, h.e_shoff, 
            h.e_flags, h.e_ehsize, h.e_phentsize, 
            h.e_phnum, h.e_shentsize, h.e_shnum,
            h.e_shstrndx
        );
    }
}

// These functions below are also used by FATELF!

/**
 * Print the ELF's class type (32/64-bit)
 * Params: c = Unsigned byte
 */
void elf_print_class(unsigned char c) {
    switch (c) {
    case 1: printf("32 "); break;
    case 2: printf("64 "); break;
    default: printf("? ");  break;
    }
}

/**
 * Print the ELF's data type (LE/BE)
 * Params: c = Unsigned byte
 */
void elf_print_data(unsigned char c) {
    switch (c) {
    case 1: printf("LE "); break;
    case 2: printf("BE "); break;
    default: printf("? ");  break;
    }
}

/**
 * Print the ELF's OS ABI (calling convention)
 * Params: c = Unsigned byte
 */
void elf_print_osabi(unsigned char c) {
    switch (c) {
    default:   printf("Unknown DECL"); break;
    case 0x00: printf("System V"); break;
    case 0x01: printf("HP-UX"); break;
    case 0x02: printf("NetBSD"); break;
    case 0x03: printf("Linux"); break;
    case 0x06: printf("Solaris"); break; 
    case 0x07: printf("AIX"); break;
    case 0x08: printf("IRIX"); break;
    case 0x09: printf("FreeBSD"); break;
    case 0x0C: printf("OpenBSD"); break;
    case 0x0D: printf("OpenVMS"); break;
    case 0x0E: printf("NonStop Kernel"); break;
    case 0x0F: printf("AROS"); break;
    case 0x10: printf("Fenix OS"); break;
    case 0x11: printf("CloudABI"); break;
    case 0x53: printf("Sortix"); break;
    }
}

/**
 * Print the ELF's type (exec/lib/etc.)
 * Params: c = Unsigned short
 */
void elf_print_type(unsigned short c) {
    switch (c) {
    default:        printf("?"); break;
    case ET_NONE:   printf("(No file type)"); break;
    case ET_REL:    printf("Relocatable"); break;
    case ET_EXEC:   printf("Executable"); break;
    case ET_DYN:    printf("Shared object"); break;
    case ET_CORE:   printf("Core"); break;
    case ET_LOPROC: printf("Professor-specific (LO)"); break;
    case ET_HIPROC: printf("Professor-specific (HI)"); break;
    }
}

/**
 * Print the ELF's machine type (system)
 * Params: c = Unsigned short
 */
void elf_print_machine(unsigned short c) {
    switch (c) {
    case EM_NONE:    printf("no"); break;
    case EM_M32:     printf("AT&T WE 32100 (M32)"); break;
    case EM_SPARC:   printf("SPARC"); break;
    case EM_860:     printf("Intel 80860"); break;
    case EM_386:     printf("x86"); break;
    case EM_IA64:    printf("IA64"); break;
    case EM_AMD64:   printf("x86-64"); break;
    case EM_68K:     printf("Motorola 68000"); break;
    case EM_88K:     printf("Motorola 88000"); break;
    case EM_MIPS:    printf("MIPS RS3000"); break;
    case EM_POWERPC: printf("PowerPC"); break;
    case EM_ARM:     printf("ARM"); break;
    case EM_SUPERH:  printf("SuperH"); break;
    case EM_AARCH64: printf("ARM (64-bit)"); break;
    default:         printf("Unknown Machine"); break;
    }
}