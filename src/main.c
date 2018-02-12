#ifdef _WIN32
#include <Windows.h>
#include <WinBase.h>
#include <tchar.h>
#include <wchar.h>
#elif __linux__
#include <glob.h>
#else // POSIX

#endif

#include <stdio.h>
#include <stdlib.h>
#include "ff.h"
#include "settings.h"
#include "utils.h"

void help() {
	puts(
		"Print file type with some information if available\n"
		"  Usage: ff FILE [OPTIONS]\n"
		"         ff OPTIONS\n"
		"\nOPTIONS\n"
		" -m        Print even more information if available\n"
		" -h        Print this help screen"
	);
}

void version() {
	printf(
#ifdef TIMESTAMP
		"ff v%s  (%s)\n"
#else
		"ff v%s\n"
#endif
		"MIT License: Copyright (c) 2017-2018 dd86k\n"
		"Project page: <https://github.com/dd86k/ff>\n",
		VERSION
#ifdef TIMESTAMP
		, TIMESTAMP
#endif
	);
}

char _args = 1;

#ifdef _WIN32
#define MAIN int wmain(int argc, wchar_t **argv)
void sa(wchar_t *a) {
#else
#define MAIN int main(int argc, char **argv)
void sa(char *a) {
#endif
	while (*++a != 0) {
		switch (*a) {
		case 'h': help(); exit(0); return;
		case 'v': version(); exit(0); return;
		case 'm': More = 1; break;
		case '-': _args = 0; break;
		}
	}
}

// CLI Options

#ifdef _WIN32
#define O_HELP L"help"
#define O_VERSION L"version"
#else
#define O_HELP "help"
#define O_VERSION "version"
#endif

#ifdef _WIN32
void sb(wchar_t *a) {
	if (_strcmpw_l(a, O_HELP, sizeof(O_HELP)/2) == 0) {
		help();
		exit(0);
	}
	if (_strcmpw_l(a, O_VERSION, sizeof(O_VERSION)/2) == 0) {
		version();
		exit(0);
	}
#else
void sb(char *a) {
	if (_strcmp_l(a, O_HELP, sizeof(O_HELP)) == 0) {
		help();
		exit(0);
	}
	if (_strcmp_l(a, O_VERSION, sizeof(O_VERSION)) == 0) {
		version();
		exit(0);
	}
#endif
}

MAIN {
	if (argc <= 1) {
		help();
		return 0;
	}
	while (--argc >= 1) {
		if (_args) {
			if (argv[argc][1] == '-') { // long arguments
				sb(argv[argc]+2);
			} else if (argv[argc][0] == '-') { // short arguments
				sa(argv[argc]);
			}
		}
#ifdef _WIN32
		unsigned int a = GetFileAttributesW(argv[argc]);
		if (a & 0x10) { // FILE_ATTRIBUTE_DIRECTORY
			report("Directory");
		} else if (a != 0xFFFFFFFF) {
				f = CreateFileW(argv[argc],
					GENERIC_READ, FILE_SHARE_READ, NULL,
					OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
				if (!f) { //TODO: GetLastError (Windows)
					puts("There was an issue opening the file.");
					return 2;
				}
				scan();
			} else {
				puts("Entry does not exist");
				return 1;
			}
		} // else
#elif __linux__
		glob_t globbuf;
		globbuf.gl_offs = 1;
		glob(argv[argc], GLOB_DOOFFS, NULL, &globbuf);
		if (globbuf.gl_pathc > 0) {
			f = fopen(argv[argc], "rb"); // maybe use _s?
			if (!f) {
				puts("There was an issue opening the file.");
				return 2;
			}
			scan();
		}
		globfree(&globbuf);
#else // POSIX

#endif
	} // while

	return 0;
}