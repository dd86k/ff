#define QED_F_BACKING_FILE 1
#define QED_F_NEED_CHECK 2
#define QED_F_BACKING_FORMAT_NO_PROBE 4

struct qed_hdr {
	//uint magic;
	uint32_t cluster_size;
	uint32_t table_size;
	uint32_t header_size;
	unsigned long long features;
	unsigned long long compat_features;
	unsigned long long autoclear_features;
	unsigned long long l1_table_offset;
	unsigned long long image_size;
	uint32_t backing_filename_offset;
	uint32_t backing_filename_size;
};

void scan_qed(void);