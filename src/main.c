#if __unix__
#include <sys/types.h>
#include <sys/stat.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include "settings.h"
#include "utils.h"

#define VERSION "0.1.1-0"

void help() {
	puts(
		"Print file type with some information if available\n"
		"  Usage: ff FILE [OPTIONS]\n"
		"         ff [OPTIONS]\n"
		"\nOPTIONS\n"
		" -m   Print even more information if available\n"
		" -s   Show name before result\n"
		" -h, -?   Print this help screen and quits\n"
		" -v       Print the version screen and quits"
	);
}

void version() {
	puts(
		"ff v" VERSION 
#ifdef TIMESTAMP
		"  (" TIMESTAMP ")"
#endif
		"\n"
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
		case 'm': ++More; break;
		case 's': ++ShowName; break;
		case '-': --_args; break;
		default:
			printf("E: -%c: Unknown argument\n", *a);
			exit(1);
		}
	}
}

// CLI Options

#ifdef _WIN32
#define O_HELP L"help"
#define O_VERSION L"version"
void sb(wchar_t *a) {
	if (_strcmpw_l(a, O_HELP, 4) == 0) {
		help();
		exit(0);
	}
	if (_strcmpw_l(a, O_VERSION, 6) == 0) {
		version();
		exit(0);
	}
	wprintf(L"E: --%s: Unknown argument\n", a);
#else
#define O_HELP "help"
#define O_VERSION "version"
void sb(char *a) {
	if (_strcmp_l(a, O_HELP, 4) == 0) {
		help();
		exit(0);
	}
	if (_strcmp_l(a, O_VERSION, 6) == 0) {
		version();
		exit(0);
	}
	printf("E: --%s: Unknown argument\n", a);
#endif
	exit(1);
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
		if (a == 0xFFFFFFFF) { // INVALID_FILE_ATTRIBUTES
			_wprintf_p(
				L"E: Entry does not exist or is invalid: %s\n",
				_currf
			);
			return 1;
		}
		if (a & 0x10) { // FILE_ATTRIBUTE_DIRECTORY
			report("Directory");
		} else if (a & 0x400) { // FILE_ATTRIBUTE_REPARSE_POINT
			report("Symbolic link");
		} else if (a != 0xFFFFFFFF) { // Not invalid
			f = CreateFileW(_currf,
				GENERIC_READ, FILE_SHARE_READ, NULL,
				OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if (!f) { //TODO: GetLastError (Windows)
				goto EWFO;
			}
			scan(); 
			CloseHandle(f);
		} else { // avoids trying to open the invalid file
EWFO:		_wprintf_p(
				L"E: There was an issue opening the file: %s\n",
				_currf
			);
			return 2;
		}
#else // POSIX
		struct stat s;
		if (stat(_currf, &s) == 0) {
			if (s.st_mode & S_IFDIR) {
				report("Directory");
			} else if (s.st_mode & S_IFREG) {
				f = fopen(_currf, "rb"); // maybe use _s?
				if (!f) {
					puts("There was an issue opening the file.");
					return 2;
				}
				scan();
				fclose(f);
			}
		} else {
			perror("E:");
		}
#endif
	} // while

	return 0;
}