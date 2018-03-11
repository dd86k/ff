struct PE_HEADER {
	uint8_t  Signature[2]; // Padding
	uint16_t Machine;
	uint16_t NumberOfSections;
	uint32_t TimeDateStamp;
	uint32_t PointerToSymbolTable;
	uint32_t NumberOfSymbols;
	uint16_t SizeOfOptionalHeader;
	uint16_t Characteristics;
};

// https://msdn.microsoft.com/en-us/library/windows/desktop/ms680339(v=vs.85).aspx
struct PE_OPTIONAL_HEADER {
	uint16_t magic; // "Format"
	uint8_t  MajorLinkerVersion;
	uint8_t  MinorLinkerVersion;
	uint32_t SizeOfCode;
	uint32_t SizeOfInitializedData;
	uint32_t SizeOfUninitializedData;
	uint32_t AddressOfEntryPoint;
	uint32_t BaseOfCode;
	uint32_t BaseOfData;
	uint32_t ImageBase;
	uint32_t SectionAlignment;
	uint32_t FileAlignment;
	uint16_t MajorOperatingSystemVersion;
	uint16_t MinorOperatingSystemVersion;
	uint16_t MajorImageVersion;
	uint16_t MinorImageVersion;
	uint16_t MajorSubsystemVersion;
	uint16_t MinorSubsystemVersion;
	uint32_t Win32VersionValue;
	uint32_t SizeOfImage;
	uint32_t SizeOfHeaders;
	uint32_t CheckSum;
	uint16_t Subsystem;
	uint16_t DllCharacteristics;
	uint32_t SizeOfStackReserve;
	uint32_t SizeOfStackCommit;
	uint32_t SizeOfHeapReserve;
	uint32_t SizeOfHeapCommit;
	uint32_t LoaderFlags; // Obsolete
	uint32_t NumberOfRvaAndSizes;
};

// IMAGE_NUMBEROF_DIRECTORY_ENTRIES = 16
struct IMAGE_DATA_DIRECTORY {
	uint64_t ExportTable;
	uint64_t ImportTable;
	uint64_t ResourceTable;
	uint64_t ExceptionTable;
	uint64_t CertificateTable;
	uint64_t BaseRelocationTable;
	uint64_t DebugDirectory;
	uint64_t ArchitectureData;
	uint64_t GlobalPtr;
	uint64_t TLSTable;
	uint64_t LoadConfigurationTable;
	uint64_t BoundImportTable;
	uint64_t ImportAddressTable;
	uint64_t DelayImport;
	uint64_t CLRHeader;
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

#define ROM   0x0107
#define HDR32 0x010B
#define HDR64 0x020B

// PE_SUBSYSTEM
#define NATIVE 1
#define WINDOWS_GUI 2
#define WINDOWS_CUI 3
#define OS2_CUI 5
#define POSIX_CUI 7
#define WINDOWS_CE_GUI 9
#define EFI_APPLICATION 10
#define EFI_BOOT_SERVICE_DRIVER 11
#define EFI_RUNTIME_DRIVER 12
#define EFI_ROM 13
#define XBOX 14
#define WINDOWS_BOOT_APPLICATION 16

void scan_pe(void);