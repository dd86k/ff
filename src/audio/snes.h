struct spc2_hdr {
	//char[5] magic;
	char magic_padding;
	uint8_t major;
	uint8_t minor;
	uint16_t entries;
};

void scan_kspc(void);