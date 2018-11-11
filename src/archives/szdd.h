struct szdd_hdr {
	char magic[4]; // halven
	uint8_t compression; // compressed mode, only 'A' is valid
	uint8_t character; // filename end character (0=unknown)
	uint32_t length; // unpacked
};

void scan_szdd(void);