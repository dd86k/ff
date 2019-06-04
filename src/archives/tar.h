#define TAR "ustar\000"
#define GNUTAR "GNUtar\00"

#define TAR32L 0x61747375
#define TAR32H 0x30300072
#define TAR64 0x3030007261747375LU

#define GNUTAR32L 0x74554E47
#define GNUTAR32H 0x30007261
#define GNUTAR64 0x3000726174554E47LU

#define NAMSIZ 100
#define TUNMLEN 32
#define TGNMLEN 32

struct tar_hdr { // POSIX 1003.1-1990
	char name[100];
	char mode[8];
	char uid[8];
	char gid[8];
	char size[12];
	char mtime[12];
	char chksum[8];
	char typeflag;
	char linkname[100];
	char magic[6];
	char version[2];
	char uname[32];
	char gname[32];
	char devmajor[8];
	char devminor[8];
//	char prefix[155];
};

void scan_tar(void);