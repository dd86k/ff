#define STARTPOS 944

struct palmdoc_hdr {
    unsigned short Compression;
    unsigned short Reserved;
    unsigned long int TextLength;
    unsigned short RecordCount;
	unsigned short RecordSize;
    union {
        unsigned long int CurrentPosition;
        struct { // MOBI
            unsigned short Encryption;
			unsigned short Reversed;
        };
    };
};

struct mobi_hdr {
    char Identifier[4]; // "MOBI"
    unsigned long int HeaderLength;
	unsigned long int Type;
	unsigned long int Encoding;
	unsigned long int UniqueID;
	unsigned long int FileVersion;
    // ...
};

void palmdb_name(void);
void scan_mobi(void);
void scan_palmdoc(void);