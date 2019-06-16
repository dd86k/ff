struct ShellLinkHeader {
	//uint32_t magic; // HeaderSize
	uint8_t clsid[16]; /// Class identifier. MUST be 00021401-0000-0000-C000-000000000046.
	uint32_t flags; /// Link attributes
	uint32_t attrs; /// File attributes
	uint64_t creation_time;
	uint64_t access_time;
	uint64_t write_time;
	uint32_t filesize;
	uint32_t icon_index;
	uint32_t show_command;
	uint16_t hotkey;
	uint16_t res1;
	uint32_t res2;
	uint32_t res3;
};

struct LinkInfoHeader {
	//uint32_t infoSize;
	uint32_t headerSize;
	uint32_t flags;
	uint32_t volumeIdOffset;
	uint32_t localBasePathOffset;
	uint32_t commonNetworkRelativeLinkOffset;
	uint32_t commonPathSuffixOffset;
	uint32_t localBasePathOffsetUnicode;
	uint32_t commonPathSuffixOffsetUnicode;
};

#define SW_SHOWNORMAL 1
#define SW_SHOWMAXIMIZED 3
#define SW_SHOWMINNOACTIVE 7

#define HasLinkTargetIDList 1	// A
#define HasLinkInfo 2	// B
#define HasName 4	// C
//#define HasVolumeID 0x 	// 
#define HasArguments 0x20	// F
#define IsUnicode 0x80	// 
#define PreferEnvironmentPath 0x1000000	// Z

#define VolumeIDAndLocalBasePath 1

#define LinkInfoHeaderSize 0x1C
#define LinkInfoHeaderMinimumExtendedSize 0x24

void scan_lnk(void);