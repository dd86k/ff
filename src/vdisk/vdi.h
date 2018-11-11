#define VDI_SUN "Sun xVM VirtualBox Disk Image >>>\n"
#define VDI     "Oracle VM VirtualBox Disk Image >>>\n"
#define VDIMAGIC 0xBEDA107F
#define VDI_IMAGE_COMMENT_SIZE 256

struct vdi_hdr { // Excludes char[64]
	uint32_t magic;
	uint16_t majorv;
	uint16_t minorv;
};
struct VDIDISKGEOMETRY {
	uint32_t cCylinders;
	uint32_t cHeads;
	uint32_t cSectors;
	uint32_t cbSector;
};
struct VDIHEADER0 { // Major v0
	uint32_t u32Type;
	uint32_t fFlags;
	char szComment[VDI_IMAGE_COMMENT_SIZE];
	struct VDIDISKGEOMETRY LegacyGeometry;
	unsigned long long cbDisk;
	uint32_t cbBlock;
	uint32_t cBlocks;
	uint32_t cBlocksAllocated;
	uint8_t uuidCreate[16];
	uint8_t uuidModify[16];
	uint8_t uuidLinkage[16];
};
struct VDIHEADER1 { // Major v1
	uint32_t cbHeader;
	uint32_t u32Type;
	uint32_t fFlags;
	char szComment[VDI_IMAGE_COMMENT_SIZE];
	uint32_t offBlocks;
	uint32_t offData;
	struct VDIDISKGEOMETRY LegacyGeometry;
	uint32_t u32Dummy;
	unsigned long long cbDisk;
	uint32_t cbBlock;
	uint32_t cbBlockExtra;
	uint32_t cBlocks;
	uint32_t cBlocksAllocated;
	uint8_t uuidCreate[16];
	uint8_t uuidModify[16];
	uint8_t uuidLinkage[16];
	uint8_t uuidParentModify[16];
};

void scan_vdi(void);