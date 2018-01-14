struct pkzip_hdr {
	//uint magic;
	unsigned short version;
	unsigned short flag;
	unsigned short compression;
	unsigned short time; // MS-DOS, 5-bit hours, 6-bit minutes, 5-bit seconds
	unsigned short date; // MS-DOS, 1980-(7-bit) year, 4-bit month, 5-bit day
	unsigned int crc32;
	unsigned int csize; // compressed size
	unsigned int usize; // uncompressed size
	unsigned short fnlength; // filename length
	unsigned short eflength; // extra field length
};

#define ENCRYPTED 1
#define ENHANCED_DEFLATION 16
#define COMPRESSED_PATCH 32
#define STRONG_ENCRYPTION 64

void scan_zip(void);