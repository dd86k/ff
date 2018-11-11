// PST magic, "!BDN"
#define PST_MAGIC 0x4E444221 
#define CLIENT_MAGIC 0x4D53

struct pst_header {
    //uint magic; // Magic
    uint32_t crc; /// CRC
    uint16_t client; /// Client magic, Must be 0x4D53
    uint16_t version_; /// File format version
    uint16_t client_version; /// Client version (based on MS-PST document version)
    uint8_t platform_create; /// Must be 0x1
    uint8_t platform_access; /// Must be 0x1
    uint32_t reserved1, reserved2;
};

struct pst_ansi {
    uint32_t nextb; /// Next page BID
    uint32_t nextp; /// Next page BID
    uint32_t unique; /// Changes everytime the PST is changed
    uint8_t rgnid[128]; /// A fixed array of 32 NIDs
    uint8_t root[40];
    uint8_t rgbrm[128];
    uint8_t rgbfp[128];
    uint8_t sentinel; /// Must be 0x80
    uint8_t crypt; /// See bCryptMethod table
    /*ushort rgbReserved;
    ubyte[12] res;
    uint res2; //3+1 ubytes from rgbReserved2 and bReserved
    ubyte[32] rgbReserved3;*/
};

struct pst_unicode {
    unsigned long long unused;
    unsigned long long nextp; /// Next page BID
    uint32_t unique; /// Changes everytime the PST is changed
    uint8_t rgnid[128]; /// A fixed array of 32 NIDs
    unsigned long long unused1;
    uint8_t root[72];
    uint32_t align_;
    uint8_t rgbrm[128];
    uint8_t rgbfp[128];
    uint8_t sentinel; /// Must be 0x80
    uint8_t crypt; /// See bCryptMethod table
    uint16_t reserved3;
    unsigned long long nextb; /// Next page BID
    uint32_t crcfull;
    /*uint res2; //3+1 ubytes from rgbReserved2 and bReserved
    ubyte[32] rgbReserved3;*/
};

void scan_pst(void);