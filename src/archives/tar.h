#define TAR "ustar\000"
#define GNUTAR "GNUtar\00"
//TODO: 64-bit number versions with conditional compile option
#define TAR32L 0x61747375
#define TAR32H 0x00202072
#define GNUTAR32L 0x74554E47
#define GNUTAR32H 0x20007261
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