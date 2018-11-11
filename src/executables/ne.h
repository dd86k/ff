// New .EXE header, found in newexe.h in the Word 1.1a source.
struct ne_hdr {
	//char[2]  ne_magic;       /* Magic number NE_MAGIC */
	uint8_t  ne_ver;         /* Version number */
	uint8_t  ne_rev;         /* Revision number */
	uint16_t ne_enttab;      /* Offset of Entry Table */
	uint16_t ne_cbenttab;    /* Number of bytes in Entry Table */
	uint32_t   ne_crc;         /* Checksum of whole file */
	uint16_t ne_flags;       /* Flag word */
	uint16_t ne_autodata;    /* Automatic data segment number */
	uint16_t ne_heap;        /* Initial heap allocation */
	uint16_t ne_stack;       /* Initial stack allocation */
	uint32_t   ne_csip;        /* Initial CS:IP setting */
	uint32_t   ne_sssp;        /* Initial SS:SP setting */
	uint16_t ne_cseg;        /* Count of file segments */
	uint16_t ne_cmod;        /* Entries in Module Reference Table */
	uint16_t ne_cbnrestab;   /* Size of non-resident name table */
	uint16_t ne_segtab;      /* Offset of Segment Table */
	uint16_t ne_rsrctab;     /* Offset of Resource Table */
	uint16_t ne_restab;      /* Offset of resident name table */
	uint16_t ne_modtab;      /* Offset of Module Reference Table */
	uint16_t ne_imptab;      /* Offset of Imported Names Table */
	uint32_t   ne_nrestab;     /* Offset of Non-resident Names Table */
	uint16_t ne_cmovent;     /* Count of movable entries */
	uint16_t ne_align;       /* Segment alignment shift count */
	uint16_t ne_cres;        /* Count of resource segments */
	uint16_t ne_psegcsum;    /* offset to segment chksums */
	uint16_t ne_pretthunks;  /* offset to return thunks */
	uint16_t ne_psegrefbytes;/* offset to segment ref. bytes */
	uint16_t ne_swaparea;    /* Minimum code swap area size */
	uint8_t  ne_expver[2];      /* Expected Windows version number */
};

enum {
	NENOTP = 0x8000, /* Not a process */
	NENONC = 0x4000, /* Non-conforming program */
	NEIERR = 0x2000, /* Errors in image */
	NEPROT = 0x0008, /* Runs in protected mode */
	NEREAL = 0x0004, /* Runs in real mode */
	NEINST = 0x0002, /* Instance data */
	NESOLO = 0x0001  /* Solo data */
};

void scan_ne(void);