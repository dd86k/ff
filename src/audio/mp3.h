struct mp3_hdr {
	uint16_t sig;
	uint8_t  info;
	uint8_t  extra;
};

struct id3_hdr {
	uint8_t  sig[3]; // "ID3"
	uint16_t ver;
	uint8_t  flags;
	union {
		uint32_t size; // Synchsafe integer
		uint8_t  sizea[4];
	};
};

struct id3_hdr_p { // Partial, no sig and majorver
	uint8_t ver;
	uint8_t flags;
	union {
		uint32_t size; // Synchsafe integer
		uint8_t  sizea[4];
	};
};

/*struct id3_frame_hdr {
	uint32_t id; // frame id
	uint32_t size;
	uint16_t flags;
};*/

void scan_mp3(uint32_t, int);
int check_mp3(uint32_t);
int skip_id3v1(void);
int skip_id3v2(void);