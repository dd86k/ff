#define EI_CLASS   4
#define EI_DATA    5
#define EI_OSABI   7
#define EI_NIDENT  16
#define EV_NONE    0
#define EV_CURRENT 1
#define ET_NONE    0      // No file type
#define ET_REL     1      // Relocatable file
#define ET_EXEC    2      // Executable file
#define ET_DYN     3      // Shared object file
#define ET_CORE    4      // Core file
#define ET_LOPROC  0xFF00 // Processor-specific
#define ET_HIPROC  0xFFFF // Processor-specific

// FatELF also uses this
#define EM_NONE        0  // No machine
#define EM_M32         1  // AT&T WE 32100
#define EM_SPARC       2  // SPARC
#define EM_386         3  // Intel Architecture
#define EM_68K         4  // Motorola 68000
#define EM_88K         5  // Motorola 88000
#define EM_860         7  // Intel 80860
#define EM_MIPS        8  // MIPS RS3000
#define EM_MIPS_RS4_BE 10 // MIPS RS4000 Big-Endian
// Rest is from http://wiki.osdev.org/ELF
#define EM_POWERPC 0x14 // PowerPC
#define EM_ARM     0x28 // ARM
#define EM_SUPERH  0xA2 // SuperH
#define EM_IA64    0x32 // Intel IA64
#define EM_AMD64   0x3E // x86-64
#define EM_AARCH64 0xB7 // 64-bit ARM

struct Elf32_Ehdr {
    unsigned char e_ident[EI_NIDENT-4]; // Excludes magic
    unsigned short e_type;
    unsigned short e_machine;
    unsigned int e_version;
    /*unsigned int e_entry; // Don't need the rest
    unsigned int e_phoff;
    unsigned int e_shoff;
    unsigned int e_flags;
    unsigned short e_ehsize;
    unsigned short e_phentsize;
    unsigned short e_phnum;
    unsigned short e_shentsize;
    unsigned short e_shnum;
    unsigned short e_shstrndx;*/
};

void scan_elf(void);
void elf_print_class(unsigned char);
void elf_print_data(unsigned char);
void elf_print_osabi(unsigned char);
void elf_print_type(unsigned short);
void elf_print_machine(unsigned short);