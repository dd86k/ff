#ifdef _WIN32
#include <Windows.h>
HANDLE f;
#else
FILE *f;
#endif

int ShowName;

void scan(void);
void report(char *);
void reportn(char *);
void report_unknown();
void report_text();