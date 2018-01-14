#define ISO "CD001"
#define BLOCK_SIZE 1024 // Usually 2048

enum { // Volume type
	BOOT = 0,
	PRIMARY_VOL_DESC
	/*SUPP_VOL_DESC,
	VOL_PART_DESC,
	VOL_TER = 255*/
};

void scan_iso(void);