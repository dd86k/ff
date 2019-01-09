#include "../utils.h"
#include "../settings.h"
#include "../ff.h"
#include "elf.h"
#include "fatelf.h"
#include <stdio.h>

// Scan a FATELF executable
void scan_fatelf() {
	struct fat_header fh;
	_ddread(&fh, sizeof(fh));

	switch (fh.version_) {
	default:
		reportf("FatELF, invalid (%d)\n", fh.version_);
		return;
	case 1: {
		struct fat_subheader_v1 fhv1;
		_ddread(&fhv1, sizeof(fhv1));

		char *c = elf_class(fhv1.word_size);
		char *d = elf_data(fhv1.byte_order);
		char *a = elf_osabi(fhv1.osabi);
		char *m = elf_machine(fhv1.machine);

		reportf("FatELF%s%s %s for %s machines\n", c, d, a, m);
		return;
	}
	}
}