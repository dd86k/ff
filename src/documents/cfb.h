struct cfb_header {
	//ulong magic;
	unsigned int magic; // reduced magic
	unsigned char clsid[16]; // CLSID_NULL
	unsigned short minor;
	unsigned short major;
	unsigned short byte_order;
	unsigned short shift; /// Sector Shift
	unsigned short mini_shift; /// Mini Sector Shift
	unsigned char res[6];
	unsigned int dir_sectors;
	unsigned int fat_sectors;
	unsigned int first_dir_sector;
	unsigned int trans_sig; /// Transaction Signature Number
	unsigned int mini_stream_cutsize;
	unsigned int first_mini_fat_loc;
	unsigned int mini_fat_sectors; /// Number of Mini FAT Sectors
	unsigned int first_difat_loc; /// First DIFAT Sector Location
	unsigned int difat_sectors; /// Number of DIFAT Sectors
	//ubyte[436] difat;
};

void scan_cfb(void);