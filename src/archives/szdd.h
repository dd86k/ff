struct szdd_hdr {
	char magic[4]; // halven
	unsigned char compression; // compressed mode, only 'A' is valid
	unsigned char character; // filename end character (0=unknown)
	unsigned int length; // unpacked
};

void scan_szdd(void);