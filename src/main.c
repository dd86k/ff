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
	fputs(
		"Simple binary file scanner\n"
		"  Usage: ff FILE [OPTIONS]\n"
		"         ff {-v|--version|-h|--help}\n"
		"\nOPTIONS\n"
		" -c    Continue on soft symbolic link\n"
		" -m    If available, print more information\n"
		" -s    Prepend filename to result\n"
		" -h, --help       Print this help screen and exit\n"
		" -v, --version    Print version screen and exit\n"
		" --license    Print license screen and exit\n",
		stdout
	);
}

void version() {
	fputs(
		"ff v" VERSION 
#ifdef TIMESTAMP
		"  (" TIMESTAMP ")"
#endif
		"\n"
		"MIT License: Copyright (c) 2017-2019 dd86k\n"
		"Project page: <https://git.dd86k.space/dd86k/ff>\n",
		stdout
	);
}

void license() {
	fputs(
		"Copyright (C) 2018-2019 dd86k\n\n"
		"Permission is hereby granted, free of charge, to any person obtaining a copy\n"
		"of this software and associated documentation files (the \"Software\"), to deal\n"
		"in the Software without restriction, including without limitation the rights\n"
		"to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\n"
		"copies of the Software, and to permit persons to whom the Software is\n"
		"furnished to do so, subject to the following conditions:\n\n"
		"The above copyright notice and this permission notice shall be included in\n"
		"all copies or substantial portions of the Software.\n\n"
		"THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n"
		"IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS\n"
		"FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS\n"
		"OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,\n"
		"WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR\n"
		"IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.\n",
		stdout
	);
}

#ifdef _WIN32
int wmain(int argc, wchar_t **argv) {
#else
int main(int argc, char **argv) {
#endif
	if (argc <= 1) help();

	char cliargs = 1;
	char clicont = 0; // on symbolic link

	int error = 0;
	while (--argc >= 1) {
		if (cliargs) {
			if (argv[argc][1] == '-') { // long arguments
#ifdef _WIN32
				wchar_t *a = argv[argc] + 2;
				if (wcscmp(a, L"help") == 0) {
					help();
					return 0;
				}
				if (wcscmp(a, L"version") == 0) {
					version();
					return 0;
				}
				if (wcscmp(a, L"license") == 0) {
					license();
					return 0;
				}
				_fwprintf_p(stderr, L"Unknown argument: --%s\n", a);
#else
				char *a = argv[argc] + 2;
				if (strcmp(a, "help") == 0) {
					help();
					return 0;
				}
				if (strcmp(a, "version") == 0) {
					version();
					return 0;
				}
				if (strcmp(a, "license") == 0) {
					version();
					return 0;
				}
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
				case 'm': ++More; break;
				case 's': ++ShowName; break;
				case 'c': ++clicont; break;
				case '-': cliargs = !cliargs; continue;
				case 'h': help(); return 0;
				case 'v': version(); return 0;
				default:
					fprintf(stderr, "Unknown argument: -%c\n", *a);
					exit(1);
				}
				continue;
			}
		} // cliargs
		currFile = argv[argc];
#ifdef _WIN32 // -- Windows --
		uint32_t a = GetFileAttributesW(currFile);
		if (a == 0xFFFFFFFF) { // INVALID_FILE_ATTRIBUTES
EWFO:			_fwprintf_p(stderr, //TODO: GetLastError (Windows)
				L"E: Could not open file: %s\n",
				currFile
			);
			return 1;
		}
		if (a & 0x10) { // FILE_ATTRIBUTE_DIRECTORY
			report("Directory");
		} else if (a & 0x400) { // FILE_ATTRIBUTE_REPARSE_POINT
			if (clicont) goto _fo;
			report("Symbolic link");
		} else { // Not invalid at this point
_fo:			f = CreateFileW(currFile,
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
		if (lstat(currFile, &s)) {
			perror("E:");
			return 1;
		}

		switch (s.st_mode & S_IFMT) { // stat(2)
		case S_IFREG:
_fo:			f = fopen(currFile, "rb"); // maybe use _s?
			if (!f) {
				fprintf(stderr, "E: Could not open file: %s\n", currFile);
				return 2;
			}
			scan(&error);
			fclose(f);
			break;
		case S_IFLNK:
			if (clicont) goto _fo;
			char p[4096];
			realpath(currFile, p); // + null terminator
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