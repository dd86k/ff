#define COWDISK_MAX_PARENT_FILELEN 1024
#define COWDISK_MAX_NAME_LEN 60
#define COWDISK_MAX_DESC_LEN 512

struct Root {
	unsigned int cylinders;
	unsigned int heads;
	unsigned int sectors;
};
struct Child {
	char parentFileName[COWDISK_MAX_PARENT_FILELEN];
	unsigned int parentGeneration;
};
struct COWDisk_Header {
	//uint magicNumber;
	unsigned int version;
	unsigned int flags;
	unsigned int numSectors;
	unsigned int grainSize;
	unsigned int gdOffset;
	unsigned int numGDEntries;
	unsigned int freeSector;
	union {
		struct Root root;
		struct Child child;
	};
	unsigned int generation;
	char name[COWDISK_MAX_NAME_LEN];
	char description[COWDISK_MAX_DESC_LEN];
	unsigned int savedGeneration;
	char reserved[8];
	unsigned int uncleanShutdown;
	//char[396] padding;
};

void scan_cowd(void);