struct ihdr_chunk_full { // Includes CRC
	uint32_t width;        // START IHDR
	uint32_t height;
	uint8_t depth;       // bit depth
	uint8_t color;       // color type
	uint8_t compression;
	uint8_t filter;
	uint8_t interlace;   // END IHDR
	uint32_t crc;
};
/*enum { // Types -- future use?
	IHDR = 0x52444849,
	pHYs = 0x73594870
}*/

void scan_png(void);