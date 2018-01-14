#define ERESWDS 0x10

struct mz_hdr {
	unsigned short e_magic;        /// Magic number
	unsigned short e_cblp;         /// Bytes on last page of file
	unsigned short e_cp;           /// Pages in file
	unsigned short e_crlc;         /// Relocations
	unsigned short e_cparh;        /// Size of header in paragraphs
	unsigned short e_minalloc;     /// Minimum extra paragraphs needed
	unsigned short e_maxalloc;     /// Maximum extra paragraphs needed
	unsigned short e_ss;           /// Initial (relative) SS value
	unsigned short e_sp;           /// Initial SP value
	unsigned short e_csum;         /// Checksum
	unsigned short e_ip;           /// Initial IP value
	unsigned short e_cs;           /// Initial (relative) CS value
	unsigned short e_lfarlc;       /// File address of relocation table
	unsigned short e_ovno;         /// Overlay number
	unsigned short e_res[ERESWDS]; /// Reserved words
	unsigned long int e_lfanew;    /// File address of new exe header (usually at 3Ch)
};

void scan_mz(void);