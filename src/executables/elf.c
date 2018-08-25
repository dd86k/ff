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
    putchar(' ');
    elf_print_type(h.e_type);
    printl(" for ");
    elf_print_machine(h.e_machine);
    puts(" machines");
}

// These functions below are also used by FATELF!

/**
 * Print the ELF's class type (32/64-bit)
 * Params: c = Unsigned byte
 */
void elf_print_class(uint8_t c) {
    switch (c) {
    case 1: printl("32 "); break;
    case 2: printl("64 "); break;
    default: printl("? ");  break;
    }
}

/**
 * Print the ELF's data type (LE/BE)
 * Params: c = Unsigned byte
 */
void elf_print_data(uint8_t c) {
    switch (c) {
    case 1: printl("LE "); break;
    case 2: printl("BE "); break;
    default: printl("? ");  break;
    }
}

/**
 * Print the ELF's OS ABI (calling convention)
 * Params: c = Unsigned byte
 */
void elf_print_osabi(uint8_t c) {
    switch (c) {
    default:   printl("DECL?"); break;
    case 0x00: printl("System V"); break;
    case 0x01: printl("HP-UX"); break;
    case 0x02: printl("NetBSD"); break;
    case 0x03: printl("Linux"); break;
    case 0x06: printl("Solaris"); break; 
    case 0x07: printl("AIX"); break;
    case 0x08: printl("IRIX"); break;
    case 0x09: printl("FreeBSD"); break;
    case 0x0C: printl("OpenBSD"); break;
    case 0x0D: printl("OpenVMS"); break;
    case 0x0E: printl("NonStop Kernel"); break;
    case 0x0F: printl("AROS"); break;
    case 0x10: printl("Fenix OS"); break;
    case 0x11: printl("CloudABI"); break;
    case 0x53: printl("Sortix"); break;
    }
}

/**
 * Print the ELF's type (exec/lib/etc.)
 * Params: c = uint16_t
 */
void elf_print_type(uint16_t c) {
    switch (c) {
    default:        printl("?"); break;
    case ET_NONE:   printl("(No file type)"); break;
    case ET_REL:    printl("Relocatable"); break;
    case ET_EXEC:   printl("Executable"); break;
    case ET_DYN:    printl("Shared object"); break;
    case ET_CORE:   printl("Core"); break;
    case ET_LOPROC: printl("Professor-specific (LO)"); break;
    case ET_HIPROC: printl("Professor-specific (HI)"); break;
    }
}

/**
 * Print the ELF's machine type (system)
 * Params: c = uint16_t
 */
void elf_print_machine(uint16_t c) {
    switch (c) {
    case EM_NONE:    printl("no"); break;
    case EM_M32:     printl("AT&T WE 32100 (M32)"); break;
    case EM_SPARC:   printl("SPARC"); break;
    case EM_860:     printl("Intel 80860"); break;
    case EM_386:     printl("x86"); break;
    case EM_IA64:    printl("IA64"); break;
    case EM_AMD64:   printl("x86-64"); break;
    case EM_68K:     printl("Motorola 68000"); break;
    case EM_88K:     printl("Motorola 88000"); break;
    case EM_MIPS:    printl("MIPS RS3000"); break;
    case EM_POWERPC: printl("PowerPC"); break;
    case EM_ARM:     printl("ARM"); break;
    case EM_SUPERH:  printl("SuperH"); break;
    case EM_AARCH64: printl("ARM (64-bit)"); break;
    default:         printl("machine?"); break;
    }
}