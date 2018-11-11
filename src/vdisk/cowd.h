#define COWDISK_MAX_PARENT_FILELEN 1024
#define COWDISK_MAX_NAME_LEN 60
#define COWDISK_MAX_DESC_LEN 512

struct Root {
	uint32_t cylinders;
	uint32_t heads;
	uint32_t sectors;
};
struct Child {
	char parentFileName[COWDISK_MAX_PARENT_FILELEN];
	uint32_t parentGeneration;
};
struct COWDisk_Header {
	//uint magicNumber;
	uint32_t version;
	uint32_t flags;
	uint32_t numSectors;
	uint32_t grainSize;
	uint32_t gdOffset;
	uint32_t numGDEntries;
	uint32_t freeSector;
	union {
		struct Root root;
		struct Child child;
	};
	uint32_t generation;
	char name[COWDISK_MAX_NAME_LEN];
	char description[COWDISK_MAX_DESC_LEN];
	uint32_t savedGeneration;
	char reserved[8];
	uint32_t uncleanShutdown;
	//char[396] padding;
};

void scan_cowd(void);