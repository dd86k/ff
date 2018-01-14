struct iscab_hdr {
	//uint magic;
	unsigned int version;
	unsigned int volumeinfo;
	unsigned int desc_offset;
	unsigned int desc_size;
};

#define LEGACY    0x000CC9B8
#define v2_20_905 0x1234001C
#define v3_00_065 0x12340016
#define v5_00_000 0x00010050

void scan_icab(void);