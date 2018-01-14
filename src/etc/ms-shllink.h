struct ShellLinkHeader {
	//unsigned int magic; // HeaderSize
	unsigned char clsid[16]; /// Class identifier. MUST be 00021401-0000-0000-C000-000000000046.
	unsigned int flags; /// Link attributes
	unsigned int attrs; /// File attributes
	unsigned long long creation_time;
	unsigned long long access_time;
	unsigned long long write_time;
	unsigned int filesize;
	unsigned int icon_index;
	unsigned int show_command;
	unsigned short hotkey;
	unsigned short res1;
	unsigned int res2;
	unsigned int res3;
};

#define SW_SHOWNORMAL 1
#define SW_SHOWMAXIMIZED 3
#define SW_SHOWMINNOACTIVE 7

#define HasLinkTargetIDList 0x1 /// A
#define HasLinkInfo 0x2 // B
/*
#define HasArguments 0x20 // F
#define IsUnicode 0x80
#define PreferEnvironmentPath 0x1000000 // Z
*/

void scan_lnk(void);