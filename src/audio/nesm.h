struct nesm_hdr {
	//char[5] magic;
	char magic_padding;
	unsigned char version;
	unsigned char total_song;
	unsigned char start_song;
	unsigned short load_add;
	unsigned short init_add;
	unsigned short play_add;
	char song_name[32];
	char song_artist[32];
	char song_copyright[32];
	unsigned short ntsc_speed; // 1/1000000th sec ticks
	unsigned char init_values[8]; // Bankswitch Init Values
	unsigned short pal_speed;
	unsigned char flag; // NTSC/PAL
	unsigned char chip;
};

void scan_nesm(void);