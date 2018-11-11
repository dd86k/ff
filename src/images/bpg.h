struct heic_hdr {
	//uint magic;
	uint8_t format; // format[8:5], alpha1[4], bit-depth-8[3:0]
	uint8_t color; // space[8:4], extension[3], alpha2[2], limited[1], animation[0]
	//uint width;  // ue7(32), exp-golomb
	//uint height; // ue7(32), exp-golomb
	//uint length; // ue7(32), exp-golomb, size?
};

// FORMAT
#define ALPHA 0x10
// COLOR
#define ANIMATION 1
#define LIMITED 2 // limited range
#define ALPHA2 4
#define EXTENSION 8

void scan_bpg(void);