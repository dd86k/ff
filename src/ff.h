#ifdef _WIN32
#include <Windows.h>
#include <WinBase.h>
#include <tchar.h>
#include <wchar.h>
HANDLE f;
#else
#include <stdio.h>
FILE *f;
#endif

#ifdef _WIN32
wchar_t *currFile;
#else
char *currFile;
#endif

void scan(int *);
void report(char *);
void reportl(char *);
void reportf(char *, ...);
void report_data();
void report_text();