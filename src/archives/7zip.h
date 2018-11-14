struct _7zip_h {
	uint16_t magic; // 2-byte leftover
	uint8_t vmajor;
	uint8_t vminor;
	uint32_t ncrc;
	uint64_t nhoffset; // next header offset
	uint64_t nhsize; // next header size
	uint32_t nhcrc; // nextheader crc
};

void scan_7zip(void);