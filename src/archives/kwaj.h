struct kwaj_hdr {
	char magic[4]; // halven
	uint16_t method; // compressed method
	uint16_t offset;
	uint16_t header; // header flag
};

#define ULENGHT 1 // 4 bytes, uncompressed data length
#define UNKNOWN 2 // 2 bytes
#define DLENGHT 4 // 2 bytes, compressed data length
#define NAME 8    // ASCIZ, filename
#define EXT 0x10  // ASCIZ, extension

void scan_kwaj(void);