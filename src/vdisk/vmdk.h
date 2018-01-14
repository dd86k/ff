struct SparseExtentHeader {
	//uint magicNumber;
	unsigned int version;
	unsigned int flags;
	unsigned long long capacity;
	unsigned long long grainSize;
	unsigned long long descriptorOffset;
	unsigned long long descriptorSize;
	unsigned int numGTEsPerGT;
	unsigned long long rgdOffset;
	unsigned long long gdOffset;
	unsigned long long overHead;
	unsigned char uncleanShutdown; // "Bool"
	char singleEndLineChar;
	char nonEndLineChar;
	char doubleEndLineChar1;
	char doubleEndLineChar2;
	unsigned short compressAlgorithm;
	//ubyte[433] pad;
};
//enum COMPRESSED = 1 << 16;

void scan_vmdk(void);