#if __unix__
#include <sys/types.h>
#include <sys/stat.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include "settings.h"
#include "utils.h"

#define VERSION "0.2.0-0"

void help() {
	puts(
		"Simple binary file scanner\n"
		"  Usage: ff FILE [OPTIONS]\n"
		"         ff [OPTIONS]\n"
		"\nOPTIONS\n"
		" -c   Continue on soft symbolic link\n"
		" -m   Print even more information if available\n"
		" -s   Show name before result\n"
		" -h, -?   Print this help screen and quits\n"
		" -v       Print the version screen and quits"
	);
	exit(0);
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
	exit(0);
}

char _args = 1;
char Continue = 0; // on symbolic link

#ifdef _WIN32
#define MAIN int wmain(int argc, wchar_t **argv)
void sa(wchar_t *a) {
#else
#define MAIN int main(int argc, char **argv)
void sa(char *a) {
#endif
	while (*++a != 0) {
		switch (*a) {
		case 'h': case '?': help(); return;
		case 'v': version(); return;
		case 'm': ++More; break;
		case 's': ++ShowName; break;
		case 'c': ++Continue; break;
		case '-': --_args; return;
		default:
			fprintf(stderr, "E: -%c: Unknown argument\n", *a);
			exit(1);
		}
	}
}

// CLI Options

#ifdef _WIN32
#define O_HELP L"help"
#define O_VERSION L"version"
void sb(wchar_t *a) {
	if (_strcmpw_l(a, O_HELP, 4) == 0)
		help();
	if (_strcmpw_l(a, O_VERSION, 6) == 0)
		version();
	_fwprintf_p(stderr, L"E: --%s: Unknown argument\n", a);
#else
#define O_HELP "help"
#define O_VERSION "version"
void sb(char *a) {
	if (_strcmp_l(a, O_HELP, 4) == 0)
		help();
	if (_strcmp_l(a, O_VERSION, 6) == 0)
		version();
	fprintf(stderr, "E: --%s: Unknown argument\n", a);
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
		uint32_t a = GetFileAttributesW(_currf);
		if (a == 0xFFFFFFFF) { // INVALID_FILE_ATTRIBUTES
EWFO:		_fwprintf_p(stderr, //TODO: GetLastError (Windows)
				L"E: Could not open file: %s\n",
				_currf
			);
			return 1;
		}
		if (a & 0x10) { // FILE_ATTRIBUTE_DIRECTORY
			report("Directory");
		} else if (a & 0x400) { // FILE_ATTRIBUTE_REPARSE_POINT
			if (Continue) goto _fo;
			report("Symbolic link");
		} else { // Not invalid at this point
_fo:		f = CreateFileW(_currf,
				GENERIC_READ, FILE_SHARE_READ, NULL,
				OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if (!f) goto EWFO;
			switch (GetFileType(f)) {
			//case 0x0001: // FILE_TYPE_DISK
			//	return 0; // Normal files fall here, because they're on disk
			case 0x0002: // FILE_TYPE_CHAR
				report("Character device");
				return 0;
			case 0x0003: // FILE_TYPE_PIPE
				report("Pipe");
				return 0;
			}
			scan();
			CloseHandle(f);
		}
#else // POSIX
		struct stat s;
		if (lstat(_currf, &s) == 0) {
			switch (s.st_mode & S_IFMT) { // stat(2)
			case S_IFBLK: report("Block device\n"); break;
			case S_IFCHR: report("Character device\n"); break;
			case S_IFDIR: report("Directory"); break;
			case S_IFIFO: report("FIFO/pipe\n"); break;
			case S_IFLNK:
				if (Continue) goto _fo;
				reportn("Symbolic link to ");
				char p[512];
				realpath(_currf, p);
				printf("\"%s\"\n", p);
				break;
			case S_IFREG:
_fo:			f = fopen(_currf, "rb"); // maybe use _s?
				if (!f) {
					fprintf(stderr, "E: Could not open file: %s\n", _currf);
					return 2;
				}
				scan();
				fclose(f);
				break;
			case S_IFSOCK: printf("Socket\n"); break;
			default: report_unknown(); break;
			}
		} else {
			perror("E:");
		}
#endif
	} // while

	return 0;
}