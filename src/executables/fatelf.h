struct fat_header {
	//uint magic; // 0x1F0E70FA
	unsigned short version_;
	unsigned char num_records;
	unsigned char reserved0;
};

struct fat_subheader_v1 {
	unsigned short machine; /* maps to e_machine. */
	unsigned char osabi;           /* maps to e_ident[EI_OSABI]. */ 
	unsigned char osabi_version;   /* maps to e_ident[EI_ABIVERSION]. */
	unsigned char word_size;       /* maps to e_ident[EI_CLASS]. */
	unsigned char byte_order;      /* maps to e_ident[EI_DATA]. */
	unsigned char reserved0;
	unsigned char reserved1;
	unsigned long long offset;
	unsigned long long size;
};

void scan_fatelf(void);