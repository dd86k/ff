// PST magic, "!BDN"
#define PST_MAGIC 0x4E444221 
#define CLIENT_MAGIC 0x4D53

struct pst_header {
    //uint magic; // Magic
    unsigned int crc; /// CRC
    unsigned short client; /// Client magic, Must be 0x4D53
    unsigned short version_; /// File format version
    unsigned short client_version; /// Client version (based on MS-PST document version)
    unsigned char platform_create; /// Must be 0x1
    unsigned char platform_access; /// Must be 0x1
    unsigned int reserved1, reserved2;
};

struct pst_ansi {
    unsigned int nextb; /// Next page BID
    unsigned int nextp; /// Next page BID
    unsigned int unique; /// Changes everytime the PST is changed
    unsigned char rgnid[128]; /// A fixed array of 32 NIDs
    unsigned char root[40];
    unsigned char rgbrm[128];
    unsigned char rgbfp[128];
    unsigned char sentinel; /// Must be 0x80
    unsigned char crypt; /// See bCryptMethod table
    /*ushort rgbReserved;
    ubyte[12] res;
    uint res2; //3+1 ubytes from rgbReserved2 and bReserved
    ubyte[32] rgbReserved3;*/
};

struct pst_unicode {
    unsigned long long unused;
    unsigned long long nextp; /// Next page BID
    unsigned int unique; /// Changes everytime the PST is changed
    unsigned char rgnid[128]; /// A fixed array of 32 NIDs
    unsigned long long unused1;
    unsigned char root[72];
    unsigned int align_;
    unsigned char rgbrm[128];
    unsigned char rgbfp[128];
    unsigned char sentinel; /// Must be 0x80
    unsigned char crypt; /// See bCryptMethod table
    unsigned short reserved3;
    unsigned long long nextb; /// Next page BID
    unsigned int crcfull;
    /*uint res2; //3+1 ubytes from rgbReserved2 and bReserved
    ubyte[32] rgbReserved3;*/
};

void scan_pst(void);