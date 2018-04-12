#define MH_MAGIC    0xFEEDFACE // Mach-O BE
#define MH_MAGIC_64 0xFEEDFACF // Mach-O BE x64
#define MH_CIGAM    0xCEFAEDFE // Mach-O LE
#define MH_CIGAM_64 0xCFFAEDFE // Mach-O LE x64
#define FAT_MAGIC   0xCAFEBABE // Mach-O FAT BE
#define FAT_CIGAM   0xBEBAFECA // Mach-O FAT LE

struct mach_header {
	// 64-bit version just adds a reserved field at the end.
//	uint32_t magic;      /* mach magic number identifier */
	uint32_t cputype;    /* cpu specifier */
	uint32_t cpusubtype; /* machine specifier */
	uint32_t filetype;   /* type of file */
	uint32_t ncmds;      /* number of load commands */
	uint32_t sizeofcmds; /* the size of all the load commands */
	uint32_t flags;      /* flags */
};

struct fatmach_header {
//	uint32_t magic;
	uint32_t nfat_arch;
};

struct fat_arch {
	uint32_t cputype;
	uint32_t cpusubtype;
	uint32_t offset;
	uint32_t size;
	uint32_t align;
};

enum cpu_type_t {
	TYPE_VAX = 1,
	TYPE_ROMP = 2,
	TYPE_NS32032 = 4,
	TYPE_NS32332 = 5,
	TYPE_MC680x0 = 6,
	TYPE_I386 = 7,
	TYPE_MIPS = 8,
	TYPE_NS32532 = 9,
	TYPE_X86_64 = 0x1000007,
	TYPE_HPPA = 11,
	TYPE_ARM = 12,
	TYPE_MC88000 = 13,
	TYPE_SPARC = 14,
	TYPE_I860 = 15, // MSB
	TYPE_I860_LITTLE = 16, // LSB
	TYPE_RS6000 = 17,
	TYPE_MC98000 = 18,
	TYPE_POWERPC = 19,
	TYPE_ABI64 = 0x1000000,
	TYPE_POWERPC64 = 1000013,
	TYPE_VEO = 255
};

// =============================
// cpu_subtype_t - CPU Subtypes, int
// =============================

// VAX subtypes
enum { // SUBTYPE_VAX
	VAX_ALL = 0,
	VAX780 = 1,
	VAX785 = 2,
	VAX750 = 3,
	VAX730 = 4,
	UVAXI = 5,
	UVAXII = 6,
	VAX8200 = 7,
	VAX8500 = 8,
	VAX8600 = 9,
	VAX8650 = 10,
	VAX8800 = 11,
	UVAXIII = 12
};

// ROMP subtypes
enum { // SUBTYPE_ROMP
	RT_ALL = 0,
	RT_PC = 1,
	RT_APC = 2,
	RT_135 = 3
};

// 32032/32332/32532 subtypes
enum { // SUBTYPE_32032
	MMAX_ALL = 0,
	MMAX_DPC = 1, /* 032 CPU */
	SQT = 2,
	MMAX_APC_FPU = 3, /* 32081 FPU */
	MMAX_APC_FPA = 4, /* Weitek FPA */
	MMAX_XPC = 5, /* 532 CPU */
};

/*uint32_t SUBTYPE_INTEL(short f, short m) {
	return f + (m << 4);
}*/

// x86 subtypes
enum { // SUBTYPE_I386
	I386_ALL = 3,
	X86_64_ALL = I386_ALL,
	_i386 = 3,
	i486 = 4,
	i486SX = 132, // "4 + 128"
	i586 = 5, // same as PENT
	PENPRO = 22,
	PENTII_M3 = 54,
	PENTII_M5 = 86,
	PENTIUM_4 = 10,
	/*PENT = SUBTYPE_INTEL(5, 0),
	PENPRO = SUBTYPE_INTEL(6, 1),
	PENTII_M3 = SUBTYPE_INTEL(6, 3),
	PENTII_M5 = SUBTYPE_INTEL(6, 5),
	PENTIUM_4 = SUBTYPE_INTEL(10, 0),*/
};

// MIPS subty
enum { // SUBTYPE_MIPS
	MIPS_ALL = 0,
	R2300 = 1,
	R2600 = 2,
	R2800 = 3,
	R2800a = 4
};

// 680x0 subtypes (m68k)
enum { // SUBTYPE_680x0
	MC680x0_ALL = 1,
	MC68030 = 1,
	MC68040 = 2,
	MC68030_ONLY = 3,
};

// HPPA subtypes
enum { // SUBTYPE_HPPA
	HPPA7100 = 0,
	HPPA7100LC = 1,
	ALL = 0,
};

// Acorn subtypes
enum { // SUBTYPE_ARM
	ACORN_ALL = 0,
	A500_ARCH = 1,
	A500 = 2,
	A440 = 3,
	M4 = 4,
	V4T = 5,
	V6 = 6,
	V5TEJ = 7,
	XSCALE = 8,
	V7 = 9,
};

// MC88000 subtypes
enum { // SUBTYPE_MC88000
	MC88000_ALL = 0,
	MMAX_JPC = 1,
	MC88100 = 1,
	MC88110 = 2,
};

// MC98000 (PowerPC) subtypes
enum { // SUBTYPE_MC98000
	MC98000_ALL = 0,
	MC98601 = 1,
};

// I860 subtypes
enum { // SUBTYPE_I860
	I860_ALL = 0,
	i860 = 1,
};

// I860_LITTLE subtypes
enum { // SUBTYPE_I860_LITTLE
	I860_LITTLE_ALL = 0,
	LITTLE = 1
};

// RS6000 subtypes
enum { // SUBTYPE_RS6000
	RS6000_ALL = 0,
	RS6000 = 1,
};

// Sun4 subtypes (port done at CMU (?))
enum { // SUBTYPE_Sun4
	SUN4_ALL = 0,
	SUN4_260 = 1,
	SUN4_110 = 2,
};

// SPARC subtypes
/*enum { // SUBTYPE_SPARC
	ALL = 0
};*/

// PowerPC subtypes
enum { // SUBTYPE_PowerPC
	POWERPC_ALL = 0,
	POWERPC_601 = 1,
	POWERPC_602 = 2,
	POWERPC_603 = 3,
	POWERPC_603e = 4,
	POWERPC_603ev = 5,
	POWERPC_604 = 6,
	POWERPC_604e = 7,
	POWERPC_620 = 8,
	POWERPC_750 = 9,
	POWERPC_7400 = 10,
	POWERPC_7450 = 11,
	POWERPC_970 = 100,
};

// VEO subtypes
enum { // SUBTYPE_VEO
	VEO_1 = 1,
	VEO_2 = 2,
	VEO_3 = 3,
	VEO_4 = 4,
	//VEO_ALL = VEO_2,
};

// ========================
/// File types
// ========================
enum filetype_t {
	FILETYPE_UNKNOWN = 0,
	MH_OBJECT      = 0x1,
	MH_EXECUTE     = 0x2,
	MH_FVMLIB      = 0x3,
	MH_CORE        = 0x4,
	MH_PRELOAD     = 0x5,
	MH_DYLIB       = 0x6,
	MH_DYLINKER    = 0x7,
	MH_BUNDLE      = 0x8,
	MH_DYLIB_STUB  = 0x9,
	MH_DSYM        = 0xA,
	MH_KEXT_BUNDLE = 0xB,
};

enum flag_t { //flag_t
	MH_NOUNDEFS                = 0x00000001,
	MH_INCRLINK                = 0x00000002,
	MH_DYLDLINK                = 0x00000004,
	MH_BINDATLOAD              = 0x00000008,
	MH_PREBOUND                = 0x00000010,
	MH_SPLIT_SEGS              = 0x00000020,
	MH_LAZY_INIT               = 0x00000040,
	MH_TWOLEVEL                = 0x00000080,
	MH_FORCE_FLAT              = 0x00000100,
	MH_NOMULTIDEFS             = 0x00000200,
	MH_NOFIXPREBINDING         = 0x00000400,
	MH_PREBINDABLE             = 0x00000800,
	MH_ALLMODSBOUND            = 0x00001000,
	MH_SUBSECTIONS_VIA_SYMBOLS = 0x00002000,
	MH_CANONICAL               = 0x00004000,
	MH_WEAK_DEFINES            = 0x00008000,
	MH_BINDS_TO_WEAK           = 0x00010000,
	MH_ALLOW_STACK_EXECUTION   = 0x00020000,
	MH_ROOT_SAFE               = 0x00040000,
	MH_SETUID_SAFE             = 0x00080000,
	MH_NO_REEXPORTED_DYLIBS    = 0x00100000,
	MH_PIE                     = 0x00200000,
	MH_DEAD_STRIPPABLE_DYLIB   = 0x00400000,
	MH_HAS_TLV_DESCRIPTORS     = 0x00800000,
	MH_NO_HEAP_EXECUTION       = 0x01000000,
	MH_APP_EXTENSION_SAFE      = 0x02000000
};

void scan_mach(uint32_t);