struct hdr_bzip {
	uint16_t sig;
	uint8_t  version;
	uint8_t  bsize; // blocksize
};

void scan_bzip(uint32_t);