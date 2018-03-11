struct gif_header {
	char magic[3];
	char version_[3];
	uint16_t width;
	uint16_t height;
	uint8_t packed;
	uint8_t bgcolor;
	uint8_t aspect; // ratio
};

#define GLOBAL_COLOR_TABLE 0x80
#define SORT_FLAG 8

void scan_gif(void);