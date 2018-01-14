#include "../utils.h"

struct PE_HEADER {
	u8  Signature[2]; // Padding
	u16 Machine;
	u16 NumberOfSections;
	u32 TimeDateStamp;
	u32 PointerToSymbolTable;
	u32 NumberOfSymbols;
	u16 SizeOfOptionalHeader;
	u16 Characteristics;
};

// https://msdn.microsoft.com/en-us/library/windows/desktop/ms680339(v=vs.85).aspx
struct PE_OPTIONAL_HEADER {
	u16 magic; // "Format"
	u8  MajorLinkerVersion;
	u8  MinorLinkerVersion;
	u32 SizeOfCode;
	u32 SizeOfInitializedData;
	u32 SizeOfUninitializedData;
	u32 AddressOfEntryPoint;
	u32 BaseOfCode;
	u32 BaseOfData;
	u32 ImageBase;
	u32 SectionAlignment;
	u32 FileAlignment;
	u16 MajorOperatingSystemVersion;
	u16 MinorOperatingSystemVersion;
	u16 MajorImageVersion;
	u16 MinorImageVersion;
	u16 MajorSubsystemVersion;
	u16 MinorSubsystemVersion;
	u32 Win32VersionValue;
	u32 SizeOfImage;
	u32 SizeOfHeaders;
	u32 CheckSum;
	u16 Subsystem;
	u16 DllCharacteristics;
	u32 SizeOfStackReserve;
	u32 SizeOfStackCommit;
	u32 SizeOfHeapReserve;
	u32 SizeOfHeapCommit;
	u32 LoaderFlags; // Obsolete
	u32 NumberOfRvaAndSizes;
};

// IMAGE_NUMBEROF_DIRECTORY_ENTRIES = 16
struct IMAGE_DATA_DIRECTORY {
	u64 ExportTable;
	u64 ImportTable;
	u64 ResourceTable;
	u64 ExceptionTable;
	u64 CertificateTable;
	u64 BaseRelocationTable;
	u64 DebugDirectory;
	u64 ArchitectureData;
	u64 GlobalPtr;
	u64 TLSTable;
	u64 LoadConfigurationTable;
	u64 BoundImportTable;
	u64 ImportAddressTable;
	u64 DelayImport;
	u64 CLRHeader;
	//ulong Reserved;
};

enum { // PE_MACHINE
	UNKNOWN = 0,
	AM33 = 0x1d3,
	AMD64 = 0x8664,
	ARM = 0x1c0,
	ARMNT = 0x1c4,
	ARM64 = 0xaa64,
	EBC = 0xebc,
	I386 = 0x14c,
	IA64 = 0x200,
	M32R = 0x9041, // LE
	MIPS16 = 0x266,
	MIPSFPU = 0x366,
	MIPSFPU16 = 0x466,
	POWERPC = 0x1f0,
	POWERPCFP = 0x1f1,
	R4000 = 0x166,
	SH3 = 0x1a2,
	SH3DSP = 0x1a3,
	SH4 = 0x1a6,
	SH5 = 0x1a8,
	THUMB = 0x1c2,
	WCEMIPSV2 = 0x169,
	// https://en.wikibooks.org/wiki/X86_Disassembly/Windows_Executable_Files
	CLR = 0xC0EE,
};

enum { // PE_CHARACTERISTIC
	RELOCS_STRIPPED = 0x0001,
	EXECUTABLE_IMAGE = 0x0002,
	LINE_NUMS_STRIPPED = 0x0004,
	LOCAL_SYMS_STRIPPED = 0x0008,
	AGGRESSIVE_WS_TRIM = 0x0010, // obsolete
	LARGE_ADDRESS_AWARE = 0x0020,
	_16BIT_MACHINE = 0x0040,
	BYTES_REVERSED_LO = 0x0080, // obsolete
	_32BIT_MACHINE = 0x0100,
	DEBUG_STRIPPED = 0x0200,
	REMOVABLE_RUN_FROM_SWAP = 0x0400,
	NET_RUN_FROM_SWAP = 0x0800,
	SYSTEM = 0x1000,
	DLL = 0x2000,
	UP_SYSTEM_ONLY = 0x4000,
	BYTES_REVERSED_HI = 0x8000 // obsolete
};

enum {
	ROM   = 0x0107,
	HDR32 = 0x010B,
	HDR64 = 0x020B
};

enum { // PE_SUBSYSTEM
	//UNKNOWN = 0,
	NATIVE = 1,
	WINDOWS_GUI = 2,
	WINDOWS_CUI = 3,
	OS2_CUI = 5,
	POSIX_CUI = 7,
	WINDOWS_CE_GUI = 9,
	EFI_APPLICATION = 10,
	EFI_BOOT_SERVICE_DRIVER = 11,
	EFI_RUNTIME_DRIVER = 12,
	EFI_ROM = 13,
	XBOX = 14,
	WINDOWS_BOOT_APPLICATION = 16
};

void scan_pe(void);