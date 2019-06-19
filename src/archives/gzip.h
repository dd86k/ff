struct hdr_gzip {
	uint16_t sig;
	uint8_t  cm;	// compression method
	uint8_t  flg;	// flags
	uint32_t mtime;	// modification time
	uint8_t  xfl;	// extra flags
	uint8_t  os;	// os filesystem
	uint16_t xlen;	// extra field length
};

#define FTEXT 1
#define FHCRC 2
#define FEXTRA 4
#define FNAME 8
#define FCOMMENT 16

void scan_gzip(void);