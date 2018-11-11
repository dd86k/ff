#define STARTPOS 944

struct palmdoc_hdr {
	uint16_t Compression;
	uint16_t Reserved;
	unsigned long int TextLength;
	uint16_t RecordCount;
	uint16_t RecordSize;
	union {
		unsigned long int CurrentPosition;
		struct { // MOBI
			uint16_t Encryption;
			uint16_t Reversed;
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