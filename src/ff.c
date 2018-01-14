#include <stdio.h>
#include "ff.h"
#include "utils.h"
#include "etc.h"
//TODO: A master header for every folder (e.g. audio/audio.h)
//      Only get scan_* functions
#include "archives/cab.h"
#include "archives/deb.h"
#include "archives/kwaj.h"
#include "archives/icab.h"
#include "archives/pst.h"
#include "archives/szdd.h"
#include "archives/rpf.h"
#include "archives/rpm.h"
#include "archives/zip.h"
#include "audio/flac.h"
#include "audio/ogg.h"
#include "audio/midi.h"
#include "audio/nesm.h"
#include "audio/snes.h"
#include "audio/wav.h"
#include "documents/cfb.h"
#include "etc/ms-shllink.h"
#include "executables/elf.h"
#include "executables/fatelf.h"
#include "executables/mach.h"
#include "executables/mz.h"
#include "images/bpg.h"
#include "images/png.h"
#include "images/flif.h"
#include "images/gif.h"
#include "images/ps.h"
#include "vdisk/vmdk.h"
#include "vdisk/cowd.h"
#include "vdisk/vhd.h"
#include "vdisk/vdi.h"
#include "vdisk/qcow2.h"
#include "vdisk/qed.h"

void scan() {
	unsigned int s;
	if (_ddread(&s, 4)) {
		puts("ERROR: Could not read file.");
		return;
	}

	switch (s) {
	case 0x00000100: {
		unsigned char b[12];
		_ddread(&b, sizeof(b));
		unsigned long int *p = (unsigned long int*)&b;
		switch (*p) { // b[0..4]
		case 0x5349534D: // "MSIS"
			report("Microsoft Money");
			return;
		case 0x6E617453: // "Stan"
			switch (p[2]) { // b[8..12]
			case 0x45434120: // " ACE"
				report("Microsoft Access 2007 database");
				return;
			case 0x74654A20: // " Jet"
				report("Microsoft Access database");
				return;
			default:
				report_unknown();
				return;
			}
		default:
			if (*b) // b[0] != 0
				report("Palm Desktop data Dile (Access)");
			else
				report("TrueType font");
			return;
		}
	}

	case 0x4D53454E: // "NESM"
		scan_nesm();
		return;

	case 0x4350534B: // "KSPC"
		scan_kspc();
		return;

	case 0x00010000:
		report("Icon, ICO format");
		return;

	case 0xBA010000:
		report("DVD Video Movie File or DVD (MPEG-2) video");
		return;

	case 0x2A004D4D: // "MM\0*"
		report("Tagged Image File Format image");
		return;

	case 0x002A4949: { // "II*\0"
		_ddread(&s, 4);
		switch (s) {
		case 0x10: // 'I' 'I' '*' 00 | 10 00 00 00 'C' 'R'
			report("Canon RAW Format Version 2 image (TIFF)");
			return;
		default:
			report("Tagged Image File Format image (TIFF)");
			return;
		}
	}

	case 0x0C000000: //TODO: Maybe get those "various" JPEG-2000 images
		report("Various JPEG-2000 image formats");
		return;

	case 0xD75F2A80: //TODO: Maybe do Kodak Cineon images
	// http://www.cineon.com/ff_draft.php
		report("Kodak Cineon image (DPX)");
		return;

	case 0x01434E52:
	case 0x02434E52: // RNC\x01 or \x02
		reportn("Rob Northen Compressed archive v");
		switch (s) { // Very lazy
		case 0x01000000: printf("2\n"); break;
		case 0x02000000: printf("1\n"); break;
		}
		return;

	case 0x58504453: // "SDPX", "XPDS"
	case 0x53445058:
		report("SMPTE DPX image");
		return;

	case 0x01312F76:
		report("OpenEXR image");
		return;

	case 0xFB475042: // "BPGû"
		scan_bpg();
		return;

	case 0xDBFFD8FF:
	case 0xE0FFD8FF:
	case 0xE1FFD8FF:
		report("Joint Photographic Experts Group image");
		return;

	case 0xCEA1A367:
		report("IMG archive");
		return;

	case 0x454C4247: // "GBLE"
	case 0x464C4247: // "GBLF"
	case 0x474C4247: // "GBLG"
	case 0x494C4247: // "GBLI"
	case 0x534C4247: // "GBLS"
	case 0x4A4C4247: // "GBLJ"
		reportn("GTA Text (GTA2+) in ");
		switch (s) {
		case 0x454C4247: printf("English\n");  break; // 'E'
		case 0x464C4247: printf("French\n");   break; // 'F'
		case 0x474C4247: printf("German\n");   break; // 'G'
		case 0x494C4247: printf("Italian\n");  break; // 'I'
		case 0x534C4247: printf("Spanish\n");  break; // 'S'
		case 0x4A4C4247: printf("Japanese\n"); break; // 'J'
		}
		return;

	case 0x47585432: { // "2TXG", big endian
		_ddread(&s, 4);
		reportn("GTA Text 2 with ");
		printf("%u entries\n", bswap32(s)); // Byte swapped
		return;
	}

	case 0x30465052: // "RPF0"
	case 0x32465052: // "RPF2"
	case 0x33465052: // "RPF3"
	case 0x34465052: // "RPF4"
	case 0x36465052: // "RPF6"
	case 0x37465052: // "RPF7"
		scan_rpf(s);
		return;

	case 0x14000000:
	case 0x18000000:
	case 0x1C000000:
	case 0x20000000: {
		unsigned int b[2];
		_ddread(&b, sizeof(b));
		switch (*b) {
		case 0x70797466: // "ftyp"
			switch (*(b + 1)) {
			case 0x6D6F7369: // "isom"
			//TODO: WARNING -- m4a is based on this
				report("ISO Base Media (MPEG-4) v1 video");
				return;
			case 0x20207471: // "qt  "
				report("QuickTime video");
				return;
			case 0x35706733: // "3gp5"
				report("MPEG-4 video");
				return;
			case 0x3234706D: // "mp42", very common!
				report("MPEG-4/QuickTime video");
				return;
			case 0x564E534D: // "MSNV"
				report("MPEG-4 video");
				return;
			case 0x2041344D: // "M4A "
				report("Apple Lossless audio (m4a)");
				return;
			default:
				switch (*(b + 1) & 0xFFFFFF) {
				case 0x706733: // "3gp"
					report("3rd Generation Partnership Project video (3gp)");
					return;
				default:
					report_unknown();
					return;
				}
			}
		default:
			report_unknown();
			return;
		}
	}

	case 0x4D524F46: { // "FORM"
		_ddseek(8, SEEK_SET);
		_ddread(&s, 4);
		switch (s) {
		// "ILBM"
		case 0x4D424C49: report("IFF Interleaved Bitmap image"); return;
		// "8SVX"
		case 0x58565338: report("IFF 8-Bit voice"); return;
		// "ACBM"
		case 0x4D424341: report("Amiga Contiguous image"); return;
		// "ANBM"
		case 0x4D424E41: report("IFF Animated image"); return;
		// "ANIM"
		case 0x4D494E41: report("IFF CEL animation"); return;
		// "FAXX"
		case 0x58584146: report("IFF Facsimile image"); return;
		// "FTXT"
		case 0x54585446: report("IFF Formatted text"); return;
		// "SMUS"
		case 0x53554D53: report("IFF Simple Musical Score"); return;
		// "CMUS"
		case 0x53554D43: report("IFF Musical Score"); return;
		// "YUVN"
		case 0x4E565559: report("IFF YUV image"); return;
		// "FANT"
		case 0x544E4146: report("Amiga Fantavision video"); return;
		// "AIFF"
		case 0x46464941: report("Audio Interchange File audio (AIFF)"); return;
		default: report_unknown(); return;
		}
	}

	case 0xB7010000:
		report("MPEG video");
		return;

	case 0x50495A4C: // "LZIP"
		report("LZIP archive");
		return;

	// Only the last signature is within the documentation.
	case 0x04034B42: // PKZIP
	case 0x06054B42: // JAR, ODF, OOXML, EPUB (PKware ZIP format)
	case 0x08074B42:
	case 0x04034B50:
		scan_zip();
		return;

	case 0x21726152: { // "Rar!"
		_ddread(&s, 3);
		switch (s) {
		case 0x01071A: //TODO: http://www.rarlab.com/technote.htm
			report("RAR archive v5.0+");
			return;
		case 0x00071A:
			report("RAR archive v1.5+");
			return;
		default:
			report_unknown();
			return;
		}
	}

	case 0x464C457F: // "\x7FELF"
		scan_elf();
		return;

	case 0x010E70FA: // FatELF
		scan_fatelf();
		return;

	case 0x474E5089: // "\x89PNG"
		scan_png();
		return;

	case MH_MAGIC: case MH_MAGIC_64: // Mach-O
	case MH_CIGAM: case MH_CIGAM_64:
	case FAT_MAGIC: case FAT_CIGAM:
		scan_mach(s);
		return;

	case 0x53502125: // "%!PS"
		report("PostScript document");
		return;

	case 0x46445025: { // "%PDF"
		char b[5] = { 0 };
		_ddread(&b, 4);
		reportn("PDF");
		printf("%s document\n", (char*)&b); // e.g. "-1.1"
		return;
	}

	case 0x75B22630: // Followed by 8E 66 CF 11 A6 D9 0 AA 0 62 CE 6C
		report("Advanced Systems audio (ASF, WMA, WMV)");
		return;

	case 0x49445324: // "$SDI"
		_ddread(&s, 4);
		switch (s) {
		case 0x31303030:
			report("Microsoft System Deployment disk");
			return;
		default:
			report_unknown();
			return;
		}

	case 0x5367674F: // "OggS"
		scan_ogg();
		return;

	case 0x43614C66: // "fLaC", big endian
		scan_flac();
		return;

	case 0x53504238: // "8BPS", Native Photoshop file
		scan_ps();
		return;

	case 0x46464952: // "RIFF", most MP2 files
		_ddseek(8, SEEK_SET);
		_ddread(&s, 4);
		switch (s) {
		case 0x45564157: // "WAVE"
			scan_wav();
			return;
		case 0x20495641: // "AVI "
			report("Audio Video Interface video (avi)");
			return;
		default:
			report_unknown();
			return;
		}

	case 0x6468544D: // "MThd", MIDI
		scan_midi();
		return;

	case 0xE011CFD0: // doc-like files, followed by 0xE11AB1A1
		scan_cfb();
		return;

	case 0x0A786564: // "dex\x0A", then follows "035\0"
		report("Dalvik executable");
		return;

	case 0x34327243: // "Cr24"
		report("Google Chrome extension or packaged app (CRX)");
		return;

	case 0x00025245: //TODO: Move this with those Apple DMG files?
		report("Roxio Toast disc or DMG (toast or dmg)");
		return;

	case 0x21726178: // "xar!"
		report("eXtensible archive (xar)");
		return;

	case 0x434F4D50: // "PMOC"
		_ddread(&s, 4);
		switch (s) {
		case 0x434F4D43: // "CMOC"
			report("USMT, Windows Files And Settings Transfer Repository");
			return;
		default:
			report_unknown();
			return;
		}

	case 0x004D4344: // "DCM\0", followed by "PA30"
		report("Windows Update Binary Delta Compression data");
		return;

	case 0xAFBC7A37: // Followed by [0x27, 0x1C]
		report("7-Zip archive (7z)");
		return;

	case 0x184D2204:
		report("LZ4 archive (lz4)");
		return;

	case 0x4643534D: // "MSCF", cab files
		scan_cab();
		return;

	case 0x28635349: // "ISc("
		scan_icab();
		return;

	case 0xA3DF451A:
		report("Matroska video (mkv, webm)");
		return;

	case 0x54265441: // "AT&T"
		_ddread(&s, 4);
		switch (s) {
		case 0x4D524F46: // "FORM"
			_ddseek(4, SEEK_CUR);
			_ddread(&s, 4);
			switch (s) {
			case 0x55564A44: // "DJVU"
				report("DjVu document, single page");
				return;
			case 0x4D564A44: // "DJVM"
				report("DjVu document, multiple pages");
				return;
			default:
				report_unknown();
				return;
			}
		default:
			report_unknown();
			return;
		}

	case 0x46464F77: // "wOFF"
		report("WOFF 1.0 font (woff)");
		return;

	case 0x32464F77: // "wOF2"
		report("WOFF 2.0 font (woff)");
		return;

	case 0x72613C21: // "!<ar", Debian Package
		scan_deb();
		return;

	case 0xDBEEABED: // RPM Package
		scan_rpm();
		return;

	case 0x44415749:   // "IWAD"
	case 0x44415750: { // "PWAD"
		int b[2]; // Reads as ints.
		_ddread(&b, sizeof(b));
		reportn(s == 0x44415750 ? "PWAD" : "IWAD");
		printf(", %d entries at %Xh\n", b[0], b[1]);
		return;
	}

	case 0x6D736100: { // "\0asm", WebAssembly binary
		// http://webassembly.org/docs/binary-encoding/
		char ver;
		_ddread(&ver, 1);
		reportn("WebAssembly v");
		printf("%d binary (wasm)\n", ver);
		return;
	}

	case 0x45555254: // "TRUE", followed by "VISION-XFILE"
		report("Truevision Targa Graphic image");
		return;

	// http://www.cabextract.org.uk/libmspack/doc/szdd_kwaj_format.html
	case 0x4A41574B: // "KWAJ"
		scan_kwaj();
		break;

	case 0x44445A53: // "SZDD"
		scan_szdd();
		break;

	case 0x0000FEFF:
		report("UTF-32+BOM (LSB) text");
		return;
	case 0xFFFE0000:
		report("UTF-32+BOM (MSB) text");
		return;

	case 0x564D444B: // "KDMV", VMDK vdisk
		scan_vmdk();
		return;

	case 0x44574F43: // "COWD", ESXi COW
		scan_cowd();
		return;

	case 0x656E6F63: // "cone", conectix, VHD
		scan_vhd();
		return;

	case 0x203C3C3C: // "<<< ", Oracle VDI vdisk
		scan_vdi();
		return;

	case 0xFB494651: // "QFI\xFB", QCOW2, big endian
		scan_qcow2();
		return;

	case 0x00444551: // "QED\0", QED
		scan_qed();
		return;

	// Apple DMG disk image
	case 0x0D730178:
	case 0x6B6F6C79: // "koly"
	case 0x6d697368: // "mish"
		report("Apple disk (dmg)");
		return;

	case 0x46494C46: // "FLIF"
		scan_flif();
		return;

	case 0x0000004C:
		scan_lnk();
		return;

	case PST_MAGIC: // "!BDN"
		scan_pst();
		return;

	case 0x00000F01:
		report("MS-SQL database");
		/* Header is 96 bytes
			POSSIBLE STRUCTURE:
			u32 magic
			u32 RedoStartLSN
			u32 BindingId
			u32 SectorSize
			u32 Status
			u32 Growth
			// ...
		*/
		return;

	default:
		switch (s & 0xFFFFFF) {
		case 0x464947: // "GIF"
			scan_gif();
			break;

		case 0x685A42: // "BZh"
			report("Bzip2 archive");
			return;

		case 0xBFBBEF:
			report("UTF-8+BOM text");
			return;

		case 0x324449: // "ID3"
			report("MPEG-2 Audio Layer III (MP3)+ID3v2 audio");
			return;

		case 0x53454E: // "NES"
			report("Nintendo Entertainment System ROM (NES)");
			return;

		case 0x0184CF:
			report("Lepton-compressed JPEG image (LEP)");
			return;

		default:
			switch ((unsigned short)s) { // MOVZX (x86)
			case 0x9D1F:
				report("Lempel-Ziv-Welch archive (RAR/ZIP)");
				return;

			case 0xA01F:
				report("LZH archive (RAR/ZIP)");
				return;

			case 0x5A4D: // "MZ"
				scan_mz();
				return;

			case 0xFEFF:
				report("UTF-16+BOM text");
				return;

			case 0xFBFF:
				report("MPEG-2 Audio Layer III (MP3) audio");
				return;

			case 0x4D42:
				report("Bitmap image (bmp)");
				return;

			case 0x8B1F:
				report("GZIP archive (gz)");
				return;

			case 0x8230:
				report("DER X.509 certificate");
				return;

			case 0x0908:
				report("Microsoft Excel BIFF8 spreadsheet");
				return;
			case 0x0904:
				report("Microsoft Excel BIFF4 spreadsheet");
				return;
			case 0x0902:
				report("Microsoft Excel BIFF3 spreadsheet");
				return;
			case 0x0900:
				report("Microsoft Excel BIFF2 spreadsheet");
				return;

			default:
				scan_etc();
				return;
			} // 2 Byte signatures
		} // 3 Byte signatures
	} // 4 Byte signatures
} // scan

void report(char *s) {
	//TODO: if -s show filename
	puts(s);
}

void reportn(char *s) {
	//TODO: if -s show filename
	printf("%s", s);
}

void report_unknown() {
	report("data");
}

void report_text() {
	report("text");
}