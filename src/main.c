#if __unix__
#include <sys/types.h>
#include <sys/stat.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "settings.h"
#include "utils.h"

#define VERSION "0.5.0"

void help() {
	printl(
	"Simple binary file scanner\n"
	"  Usage: ff FILE [OPTIONS]\n"
	"         ff {-h|--help|--version|--license}\n"
	"\nOPTIONS\n"
	" -c    Continue on soft symbolic link\n"
	" -m    If available, print more information\n"
	" -s    Prepend filename to result\n"
	" -h, --help   Print this help screen and exit\n"
	" --version    Print version screen and exit\n"
	" --license    Print license screen and exit\n"
	);
}

void version() {
	printl(
	"ff " VERSION 
#ifdef TIMESTAMP
	"  (" TIMESTAMP ")"
#endif
	"\n"
	"License: Unlicense <https://unlicense.org>\n"
	"Home: <https://git.dd86k.space/dd86k/ff>\n"
	);
}

void license() {
	printl(
	"This is free and unencumbered software released into the public domain.\n"
	"\n"
	"Anyone is free to copy, modify, publish, use, compile, sell, or\n"
	"distribute this software, either in source code form or as a compiled\n"
	"binary, for any purpose, commercial or non-commercial, and by any\n"
	"means.\n"
	"\n"
	"In jurisdictions that recognize copyright laws, the author or authors\n"
	"of this software dedicate any and all copyright interest in the\n"
	"software to the public domain. We make this dedication for the benefit\n"
	"of the public at large and to the detriment of our heirs and\n"
	"successors. We intend this dedication to be an overt act of\n"
	"relinquishment in perpetuity of all present and future rights to this\n"
	"software under copyright law.\n"
	"\n"
	"THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND,\n"
	"EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF\n"
	"MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.\n"
	"IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR\n"
	"OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,\n"
	"ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR\n"
	"OTHER DEALINGS IN THE SOFTWARE.\n"
	"\n"
	"For more information, please refer to <https://unlicense.org>\n"
	);
}

#ifdef _WIN32
int wmain(int argc, wchar_t **argv) {
#else
int main(int argc, char **argv) {
#endif
	//
	// CLI
	//

	if (argc <= 1) {
		help();
		return 0;
	}

	char cliargs = 1; // if we still take CLI options
	char clicont = 0; // on symbolic link
	int error = 0;

	while (--argc >= 1) { // note: loop does entire CLI for globbing reasons
		if (cliargs == 0) goto CLI_SKIP;

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
				license();
				return 0;
			}
			fprintf(stderr, "Unknown argument: --%s\n", a);
#endif
			return 1;
		} else if (argv[argc][0] == '-') { // short arguments
#ifdef _WIN32
			wchar_t *a = argv[argc];
#else
			char *a = argv[argc];
#endif
			while (*++a) switch (*a) {
			case 'm': More = !More; break;
			case 's': ShowName = !ShowName; break;
			case 'c': clicont = !clicont; break;
			case '-': cliargs = !cliargs; continue;
			case 'h': help(); return 0;
			default:
				fprintf(stderr, "Unknown argument: -%c\n", *a);
				return 1;
			}
			continue;
		}
CLI_SKIP:
		//
		// Main application
		//

		currFile = argv[argc];
		char *r;

#ifdef _WIN32
		//
		// Windows
		//

		uint32_t a = GetFileAttributesW(currFile);
		if (a == 0xFFFFFFFF) { // INVALID_FILE_ATTRIBUTES
G_ERROR:		_fwprintf_p(stderr, //TODO: GetLastError (Windows)
				L"Could not open file: %s\n",
				currFile
			);
			return 1;
		}
		if (a & 0x10) { // FILE_ATTRIBUTE_DIRECTORY
			r = "Directory";
		} else if (a & 0x400) { // FILE_ATTRIBUTE_REPARSE_POINT
			if (clicont) goto G_FILE;
			r = "Symbolic link";
		} else { // Not invalid at this point
G_FILE:			f = CreateFileW(currFile,
				GENERIC_READ, FILE_SHARE_READ, NULL,
				OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

			if (f == 0) goto G_ERROR;

			switch (GetFileType(f)) {
			case FILE_TYPE_DISK: // Normal files
				scan(&error);
				CloseHandle(f);
				continue;
			case FILE_TYPE_CHAR:
				r = "Character device";
				break;
			case FILE_TYPE_PIPE:
				r = "Pipe";
				break;
			case FILE_TYPE_UNKNOWN: // Better be safe than sorry
				r = "Unknown";
				break;
			}
			CloseHandle(f);
		}
		report(r);
#else
		//
		// POSIX
		//

		struct stat s;
		if (lstat(currFile, &s)) {
			perror("E:");
			return 1;
		}

		switch (s.st_mode & S_IFMT) { // stat(2)
		case S_IFREG:
G_FILE:			f = fopen(currFile, "rb");
			if (!f) {
				fprintf(stderr, "E: Could not open file: %s\n", currFile);
				return 2;
			}
			scan(&error);
			fclose(f);
			continue;
		case S_IFLNK:
			if (clicont) goto G_FILE;
			char p[4096];
			realpath(currFile, p); // + null terminator
			reportf("Symbolic link to \"%s\"\n", p);
			continue;
		case S_IFBLK: r = "Block device"; break;
		case S_IFCHR: r = "Character device"; break;
		case S_IFDIR: r = "Directory"; break;
		case S_IFIFO: r = "FIFO/pipe"; break;
		case S_IFSOCK: r = "Socket"; break;
		default: r = "Unknown"; break;
		}
		report(r);
#endif
	} // while

	return error;
}