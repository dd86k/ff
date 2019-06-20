struct xz_hdr {
	uint16_t sig; // usually 6 but 4 already read-in
	uint8_t  flg1;
	uint8_t  flg2;
	uint16_t crc32;
};

void scan_xz(void);