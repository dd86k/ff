struct ihdr_chunk_full { // Includes CRC
	unsigned int width;        // START IHDR
	unsigned int height;
	unsigned char depth;       // bit depth
	unsigned char color;       // color type
	unsigned char compression;
	unsigned char filter;
	unsigned char interlace;   // END IHDR
	unsigned int crc;
};
/*enum { // Types -- future use?
	IHDR = 0x52444849,
	pHYs = 0x73594870
}*/

void scan_png(void);