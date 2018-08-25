#include <stdio.h>
#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "ms-shllink.h"

// See [MS-SHLLINK].pdf, Microsoft
void scan_lnk() {
	struct ShellLinkHeader h;
	_ddread(&h, sizeof(h));
	reportn("Microsoft Shortcut link (MS-SHLLINK)");

	switch (h.show_command) {
	case SW_SHOWNORMAL: printl(", normal window"); break;
	case SW_SHOWMAXIMIZED: printl(", maximized"); break;
	case SW_SHOWMINNOACTIVE: printl(", minimized"); break;
	}

	if (h.hotkey) {
		printl(", hotkey (");
		int high = h.hotkey & 0xFF00;
		if (high) {
			if (high & 0x0100)
				printl("shift+");
			if (high & 0x0200)
				printl("ctrl+");
			if (high & 0x0400)
				printl("alt+");
		}
		uint8_t low = (uint8_t)h.hotkey;
		if (low) {
			if (low >= 0x30 && low <= 0x5A)
				printf("%c", low);
			else if (low >= 0x70 && low <= 0x87)
				printf("F%d", low - 0x6F); // Function keys
			else switch (low) {
				case 0x90: printl("num lock"); break;
				case 0x91: printl("scroll lock"); break;
			}
		}
		putchar(")"); // from "hotkey ("
	}

	/*if (h.flags & HasLinkTargetIDList &&
		h.flags & HasLinkInfo) {
		uint16_t l;
		_ddread(&l, 2); // Read IDListSize
		// Skip LinkTargetIDList to LinkInfo->LocalBasePath
		_ddseek(l + 47, SEEK_CUR);
		char t[255];
		_ddread(&t, sizeof(t));
		printf(", to %s", t);
	}*/

	putchar('\n');

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