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
int _ddread(void *, size_t);
/**
 * Fast seek the already opened file handle.
 * position: New position (<32-bit limit)
 * mode: File mode
 * Returns: Returns 0 if successful
 */
int _ddseek(int, int);
/**
 * Format a decimal binary number and add its appropriate suffix.
 * e.g. 24554 will result 23K
 * l: Value
 */
void _printfd(unsigned long long);
/**
 * Prints a line to stdout.
 * s: Input string
 */
void printl(char *);
/**
 * Slice an ISO9660-like string (space-padded)
 * buffer: Entry buffer
 * target: Target string
 * max   : Slice end (excluded)
 */
void isoslice(char *, char *, size_t);
void ddstrncpy(char *, char *, int);

void print_array(uint8_t *, size_t);

uint16_t bswap16(uint16_t);
uint32_t bswap32(uint32_t);
uint64_t bswap64(uint64_t);

#define GB 0x40000000
#define MB 0x100000
#define KB 0x400