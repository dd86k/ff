struct vhd_hdr {
	unsigned int magic_end; // "ctix"
	unsigned int features;
	unsigned short major;
	unsigned short minor;
	unsigned long long offset;
	unsigned int timestamp;
	char creator_app[4];
	unsigned short creator_major;
	unsigned short creator_minor;
	unsigned int creator_os;
	unsigned long long size_original;
	unsigned long long size_current;
	unsigned short cylinders;
	unsigned char heads;
	unsigned char sectors;
	unsigned int disk_type;
	unsigned int checksum;
	unsigned char uuid[16];
	unsigned char savedState;
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