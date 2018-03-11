struct rpf_hdr {
	//int magic;
	int tablesize;
	int numentries;
	int unknown0;
	int encrypted;
};

void scan_rpf(uint32_t);