struct cfb_header {
	//ulong magic;
	uint32_t magic; // reduced magic
	uint8_t clsid[16]; // CLSID_NULL
	uint16_t minor;
	uint16_t major;
	uint16_t byte_order;
	uint16_t shift; /// Sector Shift
	uint16_t mini_shift; /// Mini Sector Shift
	uint8_t res[6];
	uint32_t dir_sectors;
	uint32_t fat_sectors;
	uint32_t first_dir_sector;
	uint32_t trans_sig; /// Transaction Signature Number
	uint32_t mini_stream_cutsize;
	uint32_t first_mini_fat_loc;
	uint32_t mini_fat_sectors; /// Number of Mini FAT Sectors
	uint32_t first_difat_loc; /// First DIFAT Sector Location
	uint32_t difat_sectors; /// Number of DIFAT Sectors
	//ubyte[436] difat;
};

void scan_cfb(void);