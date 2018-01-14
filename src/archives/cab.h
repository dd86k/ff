struct cfh_hdr {
	//char[4] magic;
	unsigned int reserved1;
	unsigned int size;
	unsigned int reserved2;
	unsigned int offset;
	unsigned int reserved3;
	unsigned char minor;
	unsigned char major;
	unsigned short folders;
	unsigned short files;
	unsigned short flags;
	unsigned short id;
	unsigned short seq;
};

void scan_cab(void);