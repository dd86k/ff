struct midi_hdr {
	//char magic[4];
	unsigned long int length;
	unsigned short format;
	unsigned short number;
	unsigned short division;
};

void scan_midi(void);