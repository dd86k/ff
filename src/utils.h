#include "ff.h"
#include <stdint.h>

#ifdef _WIN32
#include <Windows.h>
#include <WinBase.h>
#endif

int _ddread(void *, size_t);
int _ddseek(long int, int);
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
unsigned long long bswap64(unsigned long long);

#define GB 1073741824
#define MB 1048576
#define KB 1024