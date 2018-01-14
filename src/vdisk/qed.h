#define QED_F_BACKING_FILE 1
#define QED_F_NEED_CHECK 2
#define QED_F_BACKING_FORMAT_NO_PROBE 4

struct qed_hdr {
	//uint magic;
	unsigned int cluster_size;
	unsigned int table_size;
	unsigned int header_size;
	unsigned long long features;
	unsigned long long compat_features;
	unsigned long long autoclear_features;
	unsigned long long l1_table_offset;
	unsigned long long image_size;
	unsigned int backing_filename_offset;
	unsigned int backing_filename_size;
};

void scan_qed(void);