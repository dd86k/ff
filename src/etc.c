#include <stdio.h> // Mostly for *nix
#include "utils.h"
#include "ff.h"
#include "etc.h"
#include "archives/iso.h"
#include "archives/tar.h"
#include "documents/mobi.h"

/**
 * Start scanning offsets for signatures
 * Note: Start seeking from the lowest value!
 */
void scan_etc() {
	if (_ddseek(0x3c, SEEK_SET) == 0) { // Palm Database Format
		unsigned long int b[2];
		_ddread(&b, sizeof(b));
		switch (b[0]) { // LOW
		case ADOBE_LOW:
			reportn("Palm Database (Adobe Reader)");
			palmdb_name();
			return;
		case BOOKMOBI_LOW:
			scan_mobi();
			return;
		case PALMDOC_LOW:
			switch (b[1]) {
			case TEALDOC_HIGH:
				reportn("Palm Database (TealDoc)");
				return;
			default:
				scan_palmdoc();
				return;
			}
			palmdb_name();
			return;
		case BDICTY_LOW:
			reportn("Palm Database (BDicty)");
			palmdb_name();
			return;
		case DB_LOW:
			reportn("Palm Database (DB)");
			palmdb_name();
			return;
		case EREADER0_LOW:
		case EREADER1_LOW:
			switch (b[1]) {
			case PLUCKER_HIGH:
				reportn("Palm Database (Plucker)");
				break;
			case QUICKSHEET_HIGH:
				reportn("Palm Database (QuickSheet)");
				break;
			case TEALMEAL_HIGH:
				reportn("Palm Database (TealMeal)");
				break;
			case TEALPAINT_HIGH:
				reportn("Palm Database (TailPaint)");
				break;
			default: // EREADER0_HIGH/EREADER1_HIGH
				reportn("Palm Database (eReader)");
				break;
			}
			palmdb_name();
			return;
		case FIREVIEWER_LOW:
			reportn("Palm Database (FireViewer)");
			palmdb_name();
			return;
		case HANDBASE_LOW:
			reportn("Palm Database (HanDBase)");
			palmdb_name();
			return;
		case INFOVIEW_LOW:
			switch (b[1]) {
			case TEALINFO_HIGH:
				reportn("Palm Database (TealInfo)");
				return;
			default:
				reportn("Palm Database (InfoView)");
				break;
			}
			palmdb_name();
			return;
		case ISILO_LOW:
			reportn("Palm Database (iSilo)");
			palmdb_name();
			return;
		case ISILO3_LOW:
			reportn("Palm Database (iSilo 3)");
			palmdb_name();
			return;
		case JFILE_LOW:
			reportn("Palm Database (JFile)");
			palmdb_name();
			return;
		case JFILEPRO_LOW:
			reportn("Palm Database (JFile Pro)");
			palmdb_name();
			return;
		case LIST_LOW:
			reportn("Palm Database (LIST)");
			palmdb_name();
			return;
		case MOBILEDB_LOW:
			reportn("Palm Database (MobileDB)");
			palmdb_name();
			return;
		case SUPERMEMO_LOW:
			reportn("Palm Database (SuperMemo)");
			palmdb_name();
			return;
		case THINKDB_LOW:
			reportn("Palm Database (ThinKDB)");
			palmdb_name();
			return;
		case TIDES_LOW:
			reportn("Palm Database (Tides)");
			palmdb_name();
			return;
		case TOMERAIDER_LOW:
			reportn("Palm Database (TomeRaider)");
			palmdb_name();
			return;
		case WEASEL_LOW:
			reportn("Palm Database (Weasel)");
			palmdb_name();
			return;
		case WORDSMITH_LOW:
			reportn("Palm Database (WordSmith)");
			palmdb_name();
			return;
		}
	} else goto _END;

	if (_ddseek(0x101, SEEK_SET) == 0) { // Tar files
		char b[sizeof(TAR)];
		_ddread(&b, sizeof(TAR));
		if (_strcmp_l(b, TAR, sizeof(TAR)) == 0 ||
			_strcmp_l(b, GNUTAR, sizeof(GNUTAR)) == 0) {
			scan_tar();
			return;
		}
	} else goto _END;

	if (_ddseek(0x8001, SEEK_SET) == 0) { // ISO files
		char b[5];
		_ddread(&b, 5);
		if (_strcmp_l(b, ISO, 5) == 0) {
			scan_iso(); return;
		}

		if (_ddseek(0x8801, SEEK_SET)) goto _END;
		_ddread(&b, 5);
		if (_strcmp_l(b, ISO, 5) == 0) {
			scan_iso(); return;
		}

		if (_ddseek(0x9001, SEEK_SET)) goto _END;
		_ddread(&b, 5);
		if (_strcmp_l(b, ISO, 5) == 0) {
			scan_iso(); return;
		}
	} //else goto _END;

_END: // If file is smaller than our seeks and/or didn't find anything
//TODO: Detect text?
	report_unknown();
}