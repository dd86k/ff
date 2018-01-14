#define C_AES 1

struct QCowHeader { //v1/v2, v3 has extra fields
	//uint magic;
	unsigned int version;
	unsigned long long backing_file_offset;
	unsigned int backing_file_size;
	unsigned int cluster_bits;
	unsigned long long size; // in bytes
	unsigned int crypt_method;
	unsigned int l1_size;
	unsigned long long l1_table_offset;
	unsigned long long refcount_table_offset;
	unsigned int refcount_table_clusters;
	unsigned int nb_snapshots;
	unsigned long long snapshots_offset;
};

void scan_qcow2(void);