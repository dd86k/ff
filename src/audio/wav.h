struct fmt_chunk {
	//char[4] id;
	unsigned int cksize;
	unsigned short format;
	unsigned short channels;
	unsigned int samplerate; // Blocks per second
	unsigned int datarate; // Bytes/s
	unsigned short blockalign;
	unsigned short samplebits; // Bits per sample
	unsigned short extensionsize;
	unsigned short nbvalidbits;
	unsigned int speakmask; // Speaker position mask
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