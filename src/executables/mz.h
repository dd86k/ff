#define ERESWDS 0x10

struct mz_hdr {
	uint16_t e_magic;        // Magic number
	uint16_t e_cblp;         // Bytes on last page of file
	uint16_t e_cp;           // Pages in file
	uint16_t e_crlc;         // Relocations
	uint16_t e_cparh;        // Size of header in paragraphs
	uint16_t e_minalloc;     // Minimum extra paragraphs needed
	uint16_t e_maxalloc;     // Maximum extra paragraphs needed
	uint16_t e_ss;           // Initial (relative) SS value
	uint16_t e_sp;           // Initial SP value
	uint16_t e_csum;         // Checksum
	uint16_t e_ip;           // Initial IP value
	uint16_t e_cs;           // Initial (relative) CS value
	uint16_t e_lfarlc;       // File address of relocation table
	uint16_t e_ovno;         // Overlay number
	uint16_t e_res[ERESWDS]; // Reserved words
	uint32_t e_lfanew;    // File address of new exe header (usually at 3Ch)
};

void scan_mz(void);