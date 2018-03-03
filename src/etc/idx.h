struct idx_header {
	//int magic; // \377t0c
	int version;
	int headerl; // header length
	int objn; // Number of objects
	// and then some other stuff
};

void scan_idx(void);