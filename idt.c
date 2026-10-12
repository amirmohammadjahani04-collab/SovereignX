#include <stdint.h>
#include "idt.h"


struct idt_entry
{
    uint16_t offset_low;
    uint16_t selector;
    uint8_t ist;
    uint8_t type_attr;
    uint16_t offset_mid;
    uint32_t offset_high;
    uint32_t zero;

} __attribute__((packed));


struct idt_entry idt[256];


void idt_set(
int n,
uint64_t handler
)
{

    idt[n].offset_low =
        handler & 0xffff;


    idt[n].offset_mid =
        (handler >> 16)
        & 0xffff;


    idt[n].offset_high =
        (handler >> 32);


    idt[n].selector =
        0x08;


    idt[n].type_attr =
        0x8E;

}


void idt_init()
{

    for(int i=0;i<256;i++)
    {
        idt_set(i,0);
    }

}
