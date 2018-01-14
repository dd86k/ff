// New .EXE header, found in newexe.h in the Word 1.1a source.
struct ne_hdr {
	//char[2]  ne_magic;       /* Magic number NE_MAGIC */
	unsigned char     ne_ver;         /* Version number */
	unsigned char     ne_rev;         /* Revision number */
	unsigned short   ne_enttab;      /* Offset of Entry Table */
	unsigned short   ne_cbenttab;    /* Number of bytes in Entry Table */
	unsigned long int     ne_crc;         /* Checksum of whole file */
	unsigned short   ne_flags;       /* Flag word */
	unsigned short   ne_autodata;    /* Automatic data segment number */
	unsigned short   ne_heap;        /* Initial heap allocation */
	unsigned short   ne_stack;       /* Initial stack allocation */
	unsigned long int     ne_csip;        /* Initial CS:IP setting */
	unsigned long int     ne_sssp;        /* Initial SS:SP setting */
	unsigned short   ne_cseg;        /* Count of file segments */
	unsigned short   ne_cmod;        /* Entries in Module Reference Table */
	unsigned short   ne_cbnrestab;   /* Size of non-resident name table */
	unsigned short   ne_segtab;      /* Offset of Segment Table */
	unsigned short   ne_rsrctab;     /* Offset of Resource Table */
	unsigned short   ne_restab;      /* Offset of resident name table */
	unsigned short   ne_modtab;      /* Offset of Module Reference Table */
	unsigned short   ne_imptab;      /* Offset of Imported Names Table */
	unsigned long int     ne_nrestab;     /* Offset of Non-resident Names Table */
	unsigned short   ne_cmovent;     /* Count of movable entries */
	unsigned short   ne_align;       /* Segment alignment shift count */
	unsigned short   ne_cres;        /* Count of resource segments */
	unsigned short   ne_psegcsum;    /* offset to segment chksums */
	unsigned short   ne_pretthunks;  /* offset to return thunks */
	unsigned short   ne_psegrefbytes;/* offset to segment ref. bytes */
	unsigned short   ne_swaparea;    /* Minimum code swap area size */
	unsigned char ne_expver[2];      /* Expected Windows version number */
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