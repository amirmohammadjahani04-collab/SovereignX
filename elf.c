#include "elf.h"


int elf_load(void *image)
{

    struct elf_header *elf =
        (struct elf_header*)image;


    if(elf->magic[0]!=0x7f)
        return 0;


    if(elf->magic[1]!='E')
        return 0;


    if(elf->magic[2]!='L')
        return 0;


    if(elf->magic[3]!='F')
        return 0;


    uint64_t entry =
        elf->entry;


    void (*program)() =
        (void(*)())entry;


    program();


    return 1;
}
