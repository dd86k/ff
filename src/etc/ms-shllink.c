#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "ms-shllink.h"
#include <inttypes.h>

// See [MS-SHLLINK].pdf, Microsoft
void scan_lnk() {
	struct ShellLinkHeader h;
	_osread(&h, sizeof(h));

	char *sc;

	switch (h.show_command) {
	case SW_SHOWMAXIMIZED: sc = "maximized"; break;
	case SW_SHOWMINNOACTIVE: sc = "minimized"; break;
	case SW_SHOWNORMAL: sc = "normal window"; break;
	default: sc = "(?)";
	}

	reportf("Microsoft Shortcut link (MS-SHLLINK), %s", sc);

	if (h.hotkey) {
		int high = h.hotkey & 0xFF00;
		printl(", hotkey (");
		if (high) {
			if (high & 0x100)
				printl("shift+");
			if (high & 0x200)
				printl("ctrl+");
			if (high & 0x400)
				printl("alt+");
		}
		uint8_t low = (uint8_t)h.hotkey;
		if (low) {
			if (low >= 0x30 && low <= 0x5A)
				printf("%c)", low);
			else if (low >= 0x70 && low <= 0x87)
				printf("F%u)", low - 0x6F); // Function keys
			else switch (low) {
				case 0x90: printl("num lock)"); break;
				case 0x91: printl("scroll lock)"); break;
			}
		}
	}

	if (h.flags & IsUnicode) {
		printl(", unicode");
	}

	if (h.flags & HasLinkTargetIDList) {
		uint16_t l;
		_osread(&l, 2); // Read IDListSize
		_osseek(l, SEEK_CUR);
	}

	if (h.flags & HasLinkInfo) {
		uint32_t l; // data length
		_osread(&l, 4); // Read LinkInfoSize
		l += 4;

		if (l < LinkInfoHeaderSize) // minimum size
			goto NO_LINK_INFO;

		uint8_t *li = malloc(l);
		_osread(li, l); // LinkInfoData
		struct LinkInfoHeader *lih = (struct LinkInfoHeader*)li;

		uint32_t hl = lih->headerSize;

		if (hl >= LinkInfoHeaderMinimumExtendedSize) { // may not work under linux
			if (lih->localBasePathOffsetUnicode) {
				printf(", to \"%.255ls\"LU\n",
					(wchar_t*)(li + lih->localBasePathOffsetUnicode - 4));
			}
			if (lih->commonPathSuffixOffsetUnicode) {
				printf(", to \"%.255ls\"CU\n",
					(wchar_t*)(li + lih->commonPathSuffixOffsetUnicode - 4));
			}
		} else if (hl == LinkInfoHeaderSize) {
			if (lih->localBasePathOffset) {
				printf(", to \"%.255s\"LA\n",
					li + lih->localBasePathOffset - 4);
			}
			if (lih->commonPathSuffixOffset) {
				printf(", to \"%.255s\"CA\n",
					li + lih->commonPathSuffixOffset - 4);
			}
		} else puts(", invalid LinkInfoHeader size");
	}
NO_LINK_INFO:

	if (More) {
		print_a("LinkCLSID: ", h.clsid, sizeof(h.clsid));
		printf(
			"LinkFlags: %Xh\n"
			"FileAttributes: %Xh\n"
			"CreationTime: %"PRIX64"h\n"
			"AccessTime: %"PRIX64"h\n"
			"WriteTime: %"PRIX64"h\n"
			"FileSize: %u\n"
			"IconIndex: %u\n",
			h.flags, h.attrs,
			h.creation_time, h.access_time, h.write_time,
			h.filesize, h.icon_index
		);
	}
}