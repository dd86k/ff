#include "ff.h"
#include <stdint.h>

#ifdef _WIN32
#include <Windows.h>
#include <WinBase.h>
#endif

/**
 * Reads from the already opened f handle defined in ff.h.
 * buffer: Void pointer to buffer
 * size: size of buffer
 * Returns: Number of bytes read
 */
int _ddread(void *buffer, size_t size);
/**
 * Fast seek the already opened file handle.
 * pos: New position (<32-bit limit)
 * mode: File mode
 * Returns: Returns 0 if successful
 */
int _ddseek(int pos, int mode);
/**
 * Format a decimal binary number and add its appropriate suffix.
 * e.g. 24554 will result 23K
 * l: Value
 */
void _printfd(unsigned long long l);
/**
 * Prints a line to stdout.
 * str: Input string
 */
void printl(char *str);
/**
 * Slice an ISO9660-like string (space-padded)
 * buffer: Entry buffer
 * target: Target string
 * max   : Slice end (excluded)
 */
void isoslice(char *buffer, char *target, size_t max);
/**
 * Copy an ascii string
 * des: Destination
 * src: Source
 * len: Length excluding null terminator
 */
void ddstrncpy(char *des, char *src, int len);

void print_array(uint8_t *, size_t);

uint16_t bswap16(uint16_t);
uint32_t bswap32(uint32_t);
uint64_t bswap64(uint64_t);

#define GOODBYE _Exit(0)

#define GB 0x40000000
#define MB 0x100000
#define KB 0x400