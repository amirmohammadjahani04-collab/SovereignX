#include <stdint.h>


#define PIC1 0x20
#define PIC2 0xA0


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


void pic_init()
{

    // شروع مقداردهی PIC

    outb(0x20,0x11);
    outb(0xA0,0x11);


    // Remap IRQ

    outb(0x21,0x20);
    outb(0xA1,0x28);


    // فعال کردن IRQ

    outb(0x21,0x00);
    outb(0xA1,0x00);

}
