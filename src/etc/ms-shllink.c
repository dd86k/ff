#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "ms-shllink.h"
#include <stdio.h>

// See [MS-SHLLINK].pdf from Microsoft.
void scan_lnk() {
	struct ShellLinkHeader h;
	_ddread(&h, sizeof(h));
	reportn("Microsoft Shortcut link (MS-SHLLINK)");

	if (h.show_command)
		switch (h.show_command) {
		case SW_SHOWNORMAL: printf(", normal window"); break;
		case SW_SHOWMAXIMIZED: printf(", maximized"); break;
		case SW_SHOWMINNOACTIVE: printf(", minimized"); break;
		}

	if (h.hotkey) {
		printf(", hotkey (");
		int high = h.hotkey & 0xFF00;
		if (high) {
			if (high & 0x0100)
				printf("shift+");
			if (high & 0x0200)
				printf("ctrl+");
			if (high & 0x0400)
				printf("alt+");
		}
		unsigned char low = (unsigned char)h.hotkey;
		if (low) {
			if (low >= 0x30 && low <= 0x5A)
				printf("%c", low);
			else if (low >= 0x70 && low <= 0x87)
				printf("F%d", low - 0x6F); // Function keys
			else switch (low) {
				case 0x90: printf("num lock"); break;
				case 0x91: printf("scroll lock"); break;
			}
		}
		printf(")"); // from "hotkey ("
	}

	/*if (h.flags & HasLinkTargetIDList &&
		h.flags & HasLinkInfo) {
		unsigned short l;
		_ddread(&l, 2); // Read IDListSize
		// Skip LinkTargetIDList to LinkInfo->LocalBasePath
		_ddseek(l + 47, SEEK_CUR);
		char t[255];
		_ddread(&t, sizeof(t));
		printf(", to %s", t);
	}*/

	puts("");

	if (More) {
		printf("LinkCLSID:");
		print_array(h.clsid, sizeof(h.clsid));
		printf(
			"LinkFlags: %Xh\n"
			"FileAttributes: %Xh\n"
			"CreationTime: %llXh\n"
			"AccessTime: %llXh\n"
			"WriteTime: %llXh\n"
			"FileSize: %Xh\n"
			"IconIndex: %Xh\n"
			"ShowCommand: %Xh\n"
			"HotKey: %Xh\n",
			h.flags, h.attrs, h.creation_time,
			h.access_time, h.write_time, h.filesize,
			h.icon_index, h.show_command, h.hotkey
		);
	}
}