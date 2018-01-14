struct flac_hdr {
	//uint magic;
	unsigned int header; // islast (1 bit) + type (7 bits) + length (24 bits)
	unsigned short minblocksize;
	unsigned short maxblocksize;
	/*
	 * Min and max frames (24 bits each)
	 * Sample rate (20 bits)
	 * # of channels (3 bits)
	 * bits per sample (5 bits)
	 * total samples (36 bits)
	 * Total : 112 bits (14 bytes)
	 */
	unsigned char stupid[14];
	unsigned char md5[16];
};

void scan_flac(void);