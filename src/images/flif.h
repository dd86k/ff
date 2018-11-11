struct flif_hdr {
	//uint magic;
	uint8_t type; // interlacing+animation[8:4], channels[3:0]
	uint8_t channelbytes; // bytes per channel
};

void scan_flif(void);