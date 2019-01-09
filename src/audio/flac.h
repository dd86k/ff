struct flac_hdr {
	//uint magic;
	uint32_t header; // islast (1 bit) + type (7 bits) + length (24 bits)
	uint16_t minblocksize;
	uint16_t maxblocksize;
	// Min and max frames (24 bits each)
	// Sample rate (20 bits)
	// number of channels (3 bits)
	// bits per sample (5 bits)
	// total samples (36 bits)
	// Total : 112 bits (14 bytes)
	uint8_t data[14];
	uint8_t md5[16];
	// block padding, registered app ID, etc.
};

void scan_flac(void);