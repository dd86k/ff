struct pkzip_hdr {
	//uint magic;
	uint16_t version;
	uint16_t flag;
	uint16_t compression;
	uint16_t time; // MS-DOS, 5-bit hours, 6-bit minutes, 5-bit seconds
	uint16_t date; // MS-DOS, 1980-(7-bit) year, 4-bit month, 5-bit day
	uint32_t crc32;
	uint32_t csize; // compressed size
	uint32_t usize; // uncompressed size
	uint16_t fnlength; // filename length
	uint16_t eflength; // extra field length
};

#define ENCRYPTED 1
#define ENHANCED_DEFLATION 16
#define COMPRESSED_PATCH 32
#define STRONG_ENCRYPTION 64

void scan_zip(void);