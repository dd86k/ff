#define C_AES 1

struct QCowHeader { //v1/v2, v3 has extra fields
	//uint magic;
	uint32_t version;
	unsigned long long backing_file_offset;
	uint32_t backing_file_size;
	uint32_t cluster_bits;
	unsigned long long size; // in bytes
	uint32_t crypt_method;
	uint32_t l1_size;
	unsigned long long l1_table_offset;
	unsigned long long refcount_table_offset;
	uint32_t refcount_table_clusters;
	uint32_t nb_snapshots;
	unsigned long long snapshots_offset;
};

void scan_qcow2(void);