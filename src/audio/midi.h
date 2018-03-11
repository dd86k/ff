struct midi_hdr {
	//char magic[4];
	unsigned long int length;
	uint16_t format;
	uint16_t number;
	uint16_t division;
};

void scan_midi(void);