#include "ff.h"
#include <stdint.h>

#ifdef _WIN32
#include <Windows.h>
#include <WinBase.h>
#endif

int _ddread(void *, size_t);
int _ddseek(int, int);
void _printfd(unsigned long long);
void printl(char *);
int _strcmp_l(char *, char *, size_t);
#ifdef _WIN32
int _strcmpw_l(wchar_t *, wchar_t *, size_t);
#endif
void isoslice(char *, char *, size_t);

void print_array(uint8_t *, size_t);

uint16_t bswap16(uint16_t);
uint32_t bswap32(uint32_t);
uint64_t bswap64(uint64_t);

#define GB 0x40000000
#define MB 0x100000
#define KB 0x400