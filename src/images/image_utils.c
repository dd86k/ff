#include "../utils.h"
/**
 * Function used in FLIF and BPG to read ue(7) values
 * Params:
 *   max = Maximum amount of bytes to travel before stopping
 * Returns: Value from current file position
 */
unsigned int fread_l(int max) {
	//TODO: Consider pointer arithmetics for ue(64) numbers!
    unsigned int r = 0; // result
    unsigned char b; // buffer
    unsigned int s = 0; // Shift
    do {
        _ddread(&b, 1);
        r |= b & 0x7F;
        if ((b & 0x80) == 0) return r;
        s += 7;
        r <<= s;
    } while (--max);

	return 0;
}