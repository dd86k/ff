struct psd_hdr {
	//unsigned short magic;
	unsigned short version;
	unsigned char reserved[6];
	unsigned short channels;
	unsigned int height;
	unsigned int width;
	unsigned short depth;
	unsigned short colormode;
};

void scan_ps();