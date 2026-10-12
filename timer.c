
#include <stdint.h>


static inline void outb(
uint16_t port,
uint8_t value
)
{
    asm volatile(
    "outb %0,%1"
    :
    :"a"(value),"Nd"(port)
    );
}



void timer_init()
{

    uint32_t frequency = 100;


    uint16_t divisor =
        1193180 / frequency;


    outb(
    0x43,
    0x36
    );


    outb(
    0x40,
    divisor & 0xff
    );


    outb(
    0x40,
    divisor >> 8
    );

}


void timer_handler()
{

    // هر تیک اینجا می‌آید

}

