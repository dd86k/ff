#if __unix__
#include <sys/types.h>
#include <sys/stat.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "settings.h"
#include "utils.h"

#define VERSION "0.4.0"

void help() {
	puts(
		"Simple binary file scanner\n"
		"  Usage: ff FILE [OPTIONS]\n"
		"         ff {-v|--version|-h|--help}\n"
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
int wmain(int argc, wchar_t **argv) {
#else
int main(int argc, char **argv) {
#endif
	if (argc <= 1) {
		help();
		return 0;
	}
	int error = 0;
	while (--argc >= 1) {
		if (_args) {
			if (argv[argc][1] == '-') { // long arguments
#ifdef _WIN32
#define O_HELP L"help"
#define O_VERSION L"version"
				wchar_t *a = argv[argc] + 2;
				if (wcscmp(a, O_HELP) == 0)
					help();
				if (wcscmp(a, O_VERSION) == 0)
					version();
				_fwprintf_p(stderr, L"Unknown argument: --%s\n", a);
#else
#define O_HELP "help"
#define O_VERSION "version"
				char *a = argv[argc] + 2;
				if (strcmp(a, O_HELP) == 0)
					help();
				if (strcmp(a, O_VERSION) == 0)
					version();
				fprintf(stderr, "Unknown argument: --%s\n", a);
#endif
				exit(1);
			} else if (argv[argc][0] == '-') { // short arguments
#ifdef _WIN32
				wchar_t *a = argv[argc];
#else
				char *a = argv[argc];
#endif
				while (*++a) switch (*a) {
				case 'h': case '?': help(); break;
				case 'v': version(); break;
				case 'm': ++More; break;
				case 's': ++ShowName; break;
				case 'c': ++Continue; break;
				case '-': --_args; continue;
				default:
					fprintf(stderr, "Unknown argument: -%c\n", *a);
					exit(1);
				}
				continue;
			}
		}
		_currf = argv[argc];
#ifdef _WIN32 // -- Windows --
		uint32_t a = GetFileAttributesW(_currf);
		if (a == 0xFFFFFFFF) { // INVALID_FILE_ATTRIBUTES
EWFO:			_fwprintf_p(stderr, //TODO: GetLastError (Windows)
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
_fo:			f = CreateFileW(_currf,
				GENERIC_READ, FILE_SHARE_READ, NULL,
				OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if (!f) goto EWFO;
			switch (GetFileType(f)) {
			//case FILE_TYPE_DISK:
			//	return 0; // Normal files fall here, because they're on disk?
			case FILE_TYPE_CHAR:
				report("Character device");
				return 0;
			case FILE_TYPE_PIPE:
				report("Pipe");
				return 0;
			case FILE_TYPE_UNKNOWN: // Better be safe than sorry
				report("Unknown");
				return 0;
			}
			scan(&error);
			CloseHandle(f);
		}
#else // -- POSIX --
		struct stat s;
		if (lstat(_currf, &s)) {
			perror("E:");
			return 1;
		}

		switch (s.st_mode & S_IFMT) { // stat(2)
		case S_IFREG:
_fo:			f = fopen(_currf, "rb"); // maybe use _s?
			if (!f) {
				fprintf(stderr, "E: Could not open file: %s\n", _currf);
				return 2;
			}
			scan(&error);
			fclose(f);
			break;
		case S_IFLNK:
			if (Continue) goto _fo;
			char p[4096];
			realpath(_currf, p); // + null terminator
			reportf("Symbolic link to \"%s\"\n", p);
			break;
		case S_IFBLK: report("Block device"); break;
		case S_IFCHR: report("Character device"); break;
		case S_IFDIR: report("Directory"); break;
		case S_IFIFO: report("FIFO/pipe"); break;
		case S_IFSOCK: report("Socket"); break;
		default: report_unknown(); break;
		}
#endif
	} // while

	return error;
}