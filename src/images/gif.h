struct gif_header {
	char magic[3];
	char version_[3];
	unsigned short width;
	unsigned short height;
	unsigned char packed;
	unsigned char bgcolor;
	unsigned char aspect; // ratio
};

#define GLOBAL_COLOR_TABLE 0x80
#define SORT_FLAG 8

void scan_gif(void);