struct rpm_hdr {
	//char[4] magic;
	uint8_t major;
	uint8_t minor;
	uint16_t type;
	uint16_t archnum;
	char name[66];
	uint16_t osnum;
	uint16_t signature_type;
	//char reserved[16];
};

void scan_rpm(void);