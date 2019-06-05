#include "utils.h" // Includes ff.h, Windows.h
#include <stdio.h>
#include <string.h>

int _ddread(void *buffer, size_t size) {
#ifdef _WIN32
	unsigned long read;
	return ReadFile(f, buffer, size, &read, NULL) == 0;
#else // POSIX
	return fread(buffer, size, 1, f) <= 0;
#endif
}

int _ddseek(int position, int mode) {
#ifdef _WIN32
	return SetFilePointer(f, position, NULL, mode) == INVALID_SET_FILE_POINTER;
#else
	return fseek(f, position, mode);
#endif
}

void printl(char *s) {
	fputs(s, stdout);
}

void isoslice(char *buffer, char *target, size_t max) {
	while (buffer[--max] == ' ' && max > 0);
	if (max > 0) {
		memcpy(target, buffer, ++max);
		*(target + max) = '\0';
	} else *target = '\0';
}

void _printfd(uint64_t l) {
	float f = l;
	if (f >= GB) { // Lazy code, sorry
		printf("%.2f GB", f / GB);
	} else if (f >= MB) {
		printf("%.1f MB", f / MB);
	} else if (f >= KB) {
		printf("%.1f KB", f / KB);
	} else
		printf("%lld B", l);
}

uint16_t bswap16(uint16_t s) {
	return s >> 8 | s << 8;
}

uint32_t bswap32(uint32_t s) {
	return
		(s & 0x000000ff) << 24 |
		(s & 0x0000ff00) << 8 |
		(s & 0x00ff0000) >> 8 |
		(s & 0xff000000) >> 24;
}

uint64_t bswap64(uint64_t s) {
	uint8_t *p = (uint8_t*)&s;
	return
		((uint64_t)p[0] << 56) |
		((uint64_t)p[1] << 40) |
		((uint64_t)p[2] << 24) |
		((uint64_t)p[3] << 8)  |
		((uint64_t)p[4] >> 8)  |
		((uint64_t)p[5] >> 24) |
		((uint64_t)p[6] >> 40) |
		((uint64_t)p[7] >> 56);
}

void print_a(char *p, uint8_t *a, size_t s) {
	size_t i = 0;
	printl(p);
	while (--s) {
		printf(" %02X", a[i]); ++i;
	}
	putchar('\n');
}