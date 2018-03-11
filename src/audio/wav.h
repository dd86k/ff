struct fmt_chunk {
	//char[4] id;
	uint32_t cksize;
	uint16_t format;
	uint16_t channels;
	uint32_t samplerate; // Blocks per second
	uint32_t datarate; // Bytes/s
	uint16_t blockalign;
	uint16_t samplebits; // Bits per sample
	uint16_t extensionsize;
	uint16_t nbvalidbits;
	uint32_t speakmask; // Speaker position mask
};
#define FMT_CHUNK 0x20746D66 // "fmt "
// Types
#define PCM 1
#define IEEE_FLOAT 3
#define ALAW 6
#define MULAW 7
#define _MP2 0x55 // Undocumented
#define EXTENSIBLE 0xFFFE

void scan_wav(void);