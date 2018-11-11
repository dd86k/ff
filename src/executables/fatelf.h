struct fat_header {
	//uint magic; // 0x1F0E70FA
	uint16_t version_;
	uint8_t num_records;
	uint8_t reserved0;
};

struct fat_subheader_v1 {
	uint16_t machine; /* maps to e_machine. */
	uint8_t osabi;           /* maps to e_ident[EI_OSABI]. */ 
	uint8_t osabi_version;   /* maps to e_ident[EI_ABIVERSION]. */
	uint8_t word_size;       /* maps to e_ident[EI_CLASS]. */
	uint8_t byte_order;      /* maps to e_ident[EI_DATA]. */
	uint8_t reserved0;
	uint8_t reserved1;
	unsigned long long offset;
	unsigned long long size;
};

void scan_fatelf(void);