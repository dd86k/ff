struct flif_hdr {
	//uint magic;
	unsigned char type; // interlacing+animation[8:4], channels[3:0]
	unsigned char channelbytes; // bytes per channel
};

void scan_flif(void);