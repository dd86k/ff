#ifdef __linux__
#include <glob.h>
#else // POSIX

#endif

#include <stdio.h>
#include <stdlib.h>
#include "ff.h"
#include "settings.h"
#include "utils.h"

#define VERSION "0.0.1-0"

void help() {
	puts(
		"Print file type with some information if available\n"
		"  Usage: ff FILE [OPTIONS]\n"
		"         ff SCREENS\n"
		"\nOPTIONS\n"
		" -m   Print even more information if available\n"
		" -s   Show name before result"
		"\nSCREENS\n"
		" -h, -?   Print this help screen and quits"
		" -v       Print the version screen and quits"
	);
}

void version() {
	puts(
#ifdef TIMESTAMP
		"ff v" VERSION "  (" TIMESTAMP ")\n"
#else
		"ff v" VERSION "\n"
#endif
		"MIT License: Copyright (c) 2017-2018 dd86k\n"
		"Project page: <https://github.com/dd86k/ff>"
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
		case 'h': case '?': help(); exit(0); return;
		case 'v': version(); exit(0); return;
		case 'm': More = 1; break;
		case 's': ShowName = 1; break;
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
	if (_strcmpw_l(a, O_HELP, 4) == 0) {
		help();
		exit(0);
	}
	if (_strcmpw_l(a, O_VERSION, 6) == 0) {
		version();
		exit(0);
	}
#else
void sb(char *a) {
	if (_strcmp_l(a, O_HELP, 4) == 0) {
		help();
		exit(0);
	}
	if (_strcmp_l(a, O_VERSION, 6) == 0) {
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
				sb(argv[argc] + 2); continue;
			} else if (argv[argc][0] == '-') { // short arguments
				sa(argv[argc]); continue;
			}
		}
		_currf = argv[argc];
#ifdef _WIN32
		unsigned int a = GetFileAttributesW(_currf);
		if (a & 0x10) { // FILE_ATTRIBUTE_DIRECTORY
			report("Directory");
		} else if (a != 0xFFFFFFFF) { // not INVALID
			f = CreateFileW(_currf,
				GENERIC_READ, FILE_SHARE_READ, NULL,
				OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if (!f) { //TODO: GetLastError (Windows)
				puts("There was an issue opening the file.");
				return 2;
			}
			scan();
			CloseHandle(f);
		} else {
			puts("Entry does not exist");
			return 1;
		}
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
			fclose(f);
		}
		globfree(&globbuf);
#else // POSIX

#endif
	} // while

	return 0;
}