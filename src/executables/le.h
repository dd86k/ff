struct e32_hdr {
	//char[2] e32_magic; // "LX" or "LE"
	uint8_t e32_border;  // Byte order
	uint8_t e32_worder;  // Word order
	unsigned long int e32_level;    // LE/LX Version
	uint16_t e32_cpu;    // CPU
	uint16_t e32_os;     // OS
	unsigned long int e32_ver;      // Module version
	unsigned long int e32_mflags;   // Module flags
	unsigned long int e32_mpages;   // # Module pages
	unsigned long int e32_startobj; // Object # for IP
	unsigned long int e32_eip;      // Extended IP
	// And these are the most interesting parts.
};

enum {
	OS2 = 1,
	Windows,
	DOS4,
	Windows386
};

enum {
	i286 = 1,
	_i386,
	i486
};

enum {
	Library = 0x8000,
	ProtectedMemoryLibrary = 0x18000,
	PhysicalDeviceDriver = 0x20000,
	VirtualDeiveDriver = 0x28000
};

void scan_le(int);