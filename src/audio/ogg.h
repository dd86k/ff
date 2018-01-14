struct ogg_hdr {
	//uint magic;
	unsigned char version;
	unsigned char type; // Usually bit 2 set
	unsigned long long granulepos;
	unsigned int serialnum;
	unsigned int pageseqnum;
	unsigned int crc32;
	unsigned char pages;
};

void scan_ogg(void);