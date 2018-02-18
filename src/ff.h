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
wchar_t *_currf;
#else
char *_currf;
#endif

void scan(void);
void report(char *);
void reportn(char *);
void report_unknown();
void report_text();