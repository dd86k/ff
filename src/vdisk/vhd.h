struct vhd_hdr {
	uint32_t magic_end; // "ctix"
	uint32_t features;
	uint16_t major;
	uint16_t minor;
	unsigned long long offset;
	uint32_t timestamp;
	char creator_app[4];
	uint16_t creator_major;
	uint16_t creator_minor;
	uint32_t creator_os;
	unsigned long long size_original;
	unsigned long long size_current;
	uint16_t cylinders;
	uint8_t heads;
	uint8_t sectors;
	uint32_t disk_type;
	uint32_t checksum;
	uint8_t uuid[16];
	uint8_t savedState;
	//ubyte[427] reserved;
};

#define VHDMAGIC "conectix"
#define OS_WINDOWS 0x6b326957 // "Wi2k"
#define OS_MAC 0x2063614d // "Mac "
#define F_TEMPORARY 1
#define F_RES 2 // reserved, always set
#define D_FIXED 2
#define D_DYNAMIC 3
#define D_DIFF 4

void scan_vhd(void);