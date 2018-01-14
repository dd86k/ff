#define VDI_SUN "Sun xVM VirtualBox Disk Image >>>\n"
#define VDI     "Oracle VM VirtualBox Disk Image >>>\n"
#define VDIMAGIC 0xBEDA107F
#define VDI_IMAGE_COMMENT_SIZE 256

struct vdi_hdr { // Excludes char[64]
	unsigned int magic;
	unsigned short majorv;
	unsigned short minorv;
};
struct VDIDISKGEOMETRY {
	unsigned int cCylinders;
	unsigned int cHeads;
	unsigned int cSectors;
	unsigned int cbSector;
};
struct VDIHEADER0 { // Major v0
	unsigned int u32Type;
	unsigned int fFlags;
	char szComment[VDI_IMAGE_COMMENT_SIZE];
	struct VDIDISKGEOMETRY LegacyGeometry;
	unsigned long long cbDisk;
	unsigned int cbBlock;
	unsigned int cBlocks;
	unsigned int cBlocksAllocated;
	unsigned char uuidCreate[16];
	unsigned char uuidModify[16];
	unsigned char uuidLinkage[16];
};
struct VDIHEADER1 { // Major v1
	unsigned int cbHeader;
	unsigned int u32Type;
	unsigned int fFlags;
	char szComment[VDI_IMAGE_COMMENT_SIZE];
	unsigned int offBlocks;
	unsigned int offData;
	struct VDIDISKGEOMETRY LegacyGeometry;
	unsigned int u32Dummy;
	unsigned long long cbDisk;
	unsigned int cbBlock;
	unsigned int cbBlockExtra;
	unsigned int cBlocks;
	unsigned int cBlocksAllocated;
	unsigned char uuidCreate[16];
	unsigned char uuidModify[16];
	unsigned char uuidLinkage[16];
	unsigned char uuidParentModify[16];
};

void scan_vdi(void);