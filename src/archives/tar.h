#define TAR "ustar\000"
#define GNUTAR "GNUtar\00"
#define NAMSIZ 100
#define TUNMLEN 32
#define TGNMLEN 32

struct tar_hdr {
	char name[NAMSIZ];
	char mode[8];
	char uid[8];
	char gid[8];
	char size[12];
	char mtime[12];
	char chksum[8];
	char linkflag;
	char linkname[NAMSIZ];
	char magic[8];
	char uname[TUNMLEN];
	char gname[TGNMLEN];
	char devmajor[8];
	char devminor[8];
};

void scan_tar(void);