struct spc2_hdr {
	//char[5] magic;
	char magic_padding;
	unsigned char major;
	unsigned char minor;
	unsigned short entries;
};

void scan_kspc(void);