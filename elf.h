#ifndef ELF_H
#define ELF_H

#include <stdint.h>

struct elf_header
{
    unsigned char magic[4];

    uint8_t bits;

    uint64_t entry;

    uint64_t phoff;

    uint16_t phnum;

};


int elf_load(
void *image
);


#endif
