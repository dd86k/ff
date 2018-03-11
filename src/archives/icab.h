struct iscab_hdr {
	//uint magic;
	uint32_t version;
	uint32_t volumeinfo;
	uint32_t desc_offset;
	uint32_t desc_size;
};

#define LEGACY    0x000CC9B8
#define v2_20_905 0x1234001C
#define v3_00_065 0x12340016
#define v5_00_000 0x00010050

void scan_icab(void);