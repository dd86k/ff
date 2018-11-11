struct psd_hdr {
	//uint16_t magic;
	uint16_t version;
	uint8_t reserved[6];
	uint16_t channels;
	uint32_t height;
	uint32_t width;
	uint16_t depth;
	uint16_t colormode;
};

void scan_ps();