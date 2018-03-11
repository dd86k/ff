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
    uint8_t e_ident[EI_NIDENT-4]; // Excludes magic
    uint16_t e_type;
    uint16_t e_machine;
    uint32_t e_version;
    /*uint32_t e_entry; // Don't need the rest
    uint32_t e_phoff;
    uint32_t e_shoff;
    uint32_t e_flags;
    uint16_t e_ehsize;
    uint16_t e_phentsize;
    uint16_t e_phnum;
    uint16_t e_shentsize;
    uint16_t e_shnum;
    uint16_t e_shstrndx;*/
};

void scan_elf(void);
void elf_print_class(uint8_t);
void elf_print_data(uint8_t);
void elf_print_osabi(uint8_t);
void elf_print_type(uint16_t);
void elf_print_machine(uint16_t);