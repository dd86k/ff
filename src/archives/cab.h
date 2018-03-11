struct cfh_hdr {
	//char[4] magic;
	uint32_t reserved1;
	uint32_t size;
	uint32_t reserved2;
	uint32_t offset;
	uint32_t reserved3;
	uint8_t minor;
	uint8_t major;
	uint16_t folders;
	uint16_t files;
	uint16_t flags;
	uint16_t id;
	uint16_t seq;
};

void scan_cab(void);