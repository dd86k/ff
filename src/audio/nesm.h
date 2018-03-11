struct nesm_hdr {
	//char[5] magic;
	char magic_padding;
	uint8_t version;
	uint8_t total_song;
	uint8_t start_song;
	uint16_t load_add;
	uint16_t init_add;
	uint16_t play_add;
	char song_name[32];
	char song_artist[32];
	char song_copyright[32];
	uint16_t ntsc_speed; // 1/1000000th sec ticks
	uint8_t init_values[8]; // Bankswitch Init Values
	uint16_t pal_speed;
	uint8_t flag; // NTSC/PAL
	uint8_t chip;
};

void scan_nesm(void);