struct kwaj_hdr {
	char magic[4]; // halven
	unsigned short method; // compressed method
	unsigned short offset;
	unsigned short header; // header flag
};

#define ULENGHT 1 // 4 bytes, uncompressed data length
#define UNKNOWN 2 // 2 bytes
#define DLENGHT 4 // 2 bytes, compressed data length
#define NAME 8    // ASCIZ, filename
#define EXT 0x10  // ASCIZ, extension

void scan_kwaj(void);