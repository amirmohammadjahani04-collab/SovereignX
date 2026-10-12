#include <stdint.h>
#include "gdt.h"


struct gdt_entry
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));


struct gdt_entry gdt[3];


void gdt_set(
int num,
uint32_t base,
uint32_t limit,
uint8_t access,
uint8_t gran
)
{

    gdt[num].base_low =
        base & 0xffff;

    gdt[num].base_middle =
        (base >> 16) & 0xff;

    gdt[num].base_high =
        (base >> 24) & 0xff;


    gdt[num].limit_low =
        limit & 0xffff;

    gdt[num].granularity =
        (limit >> 16) & 0x0f;


    gdt[num].granularity |=
        gran & 0xf0;


    gdt[num].access =
        access;
}


void gdt_init()
{

    gdt_set(
    0,
    0,
    0,
    0,
    0
    );


    // Code Segment

    gdt_set(
    1,
    0,
    0xfffff,
    0x9A,
    0xA0
    );


    // Data Segment

    gdt_set(
    2,
    0,
    0xfffff,
    0x92,
    0xA0
    );

}
