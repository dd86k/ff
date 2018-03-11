struct ogg_hdr {
	//uint magic;
	uint8_t version;
	uint8_t type; // Usually bit 2 set
	unsigned long long granulepos;
	uint32_t serialnum;
	uint32_t pageseqnum;
	uint32_t crc32;
	uint8_t pages;
};

void scan_ogg(void);