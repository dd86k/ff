#include "ff.h"
#include <stdint.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

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

void print_array(unsigned char *, size_t);

unsigned short bswap16(unsigned short);
unsigned int bswap32(unsigned int);
unsigned long long bswap64(unsigned long long);

#define GB 1073741824
#define MB 1048576
#define KB 1024