struct deb_hdr {
	char magic[4]; // "!<arch>\n", halven to avoid rewind
	char file_iden[16]; // "debian-binary   "
	char timestamp[12];
	char uid[6];
	char gid[6];
	char filemode[8];
	char filesize[10];
	char END[2];
	char version[3];
	char ENDV;
	char ctl_file_ident[16];
	char ctl_timestamp[12];
	char ctl_uid[6];
	char ctl_gid[6];
	char ctl_filemode[8];
	char ctl_filesize[10];
	char CTL_END[2];
};
struct deb_data_hdr {
	char file_ident[16];
	char timestamp[12];
	char uid[6];
	char gid[6];
	char filemode[8];
	char filesize[10];
	char END[2];
};

#define DEBIANBIN "debian-binary   "

void scan_deb(void);