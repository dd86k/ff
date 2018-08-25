#include "../utils.h"

/**
 * Function used in FLIF and BPG to read ue(7) values
 * Params:
 *   max = Maximum amount of bytes to travel before stopping
 * Returns: Value from current file position
 */
uint32_t fread_l(int max) {
	//TODO: Consider pointer arithmetics for ue(64) numbers!
	uint32_t r = 0; // result
	uint8_t b; // buffer
	uint32_t s = 0; // Shift
	do {
		_ddread(&b, 1);
		r |= b & 0x7F;
		if ((b & 0x80) == 0) return r;
		s += 7;
		r <<= s;
	} while (--max);

	return 0;
}