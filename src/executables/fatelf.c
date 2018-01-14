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

	reportn("FatELF");

	switch (fh.version_) {
		default:
			printf(" with invalid version (%d)", fh.version_);
			return;
		case 1: {
			struct fat_subheader_v1 fhv1;
			_ddread(&fhv1, sizeof(fhv1));

			elf_print_class(fhv1.word_size);
			elf_print_data(fhv1.byte_order);
			elf_print_osabi(fhv1.osabi);
			printf(" binary for ");
			elf_print_machine(fhv1.machine);
			printf(" machines");
			break;
		}
	}

	puts("");
}