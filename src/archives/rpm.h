struct rpm_hdr {
	//char[4] magic;
	unsigned char major;
	unsigned char minor;
	unsigned short type;
	unsigned short archnum;
	char name[66];
	unsigned short osnum;
	unsigned short signature_type;
	//char reserved[16];
};

void scan_rpm(void);