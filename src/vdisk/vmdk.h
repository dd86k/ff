struct SparseExtentHeader {
	//uint magicNumber;
	uint32_t version;
	uint32_t flags;
	unsigned long long capacity;
	unsigned long long grainSize;
	unsigned long long descriptorOffset;
	unsigned long long descriptorSize;
	uint32_t numGTEsPerGT;
	unsigned long long rgdOffset;
	unsigned long long gdOffset;
	unsigned long long overHead;
	uint8_t uncleanShutdown; // "Bool"
	char singleEndLineChar;
	char nonEndLineChar;
	char doubleEndLineChar1;
	char doubleEndLineChar2;
	uint16_t compressAlgorithm;
	//ubyte[433] pad;
};
//enum COMPRESSED = 1 << 16;

void scan_vmdk(void);