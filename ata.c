#include <stdint.h>

static inline void outb(uint16_t port,uint8_t value)
{
    asm volatile(
        "outb %0,%1"
        :
        :"a"(value),"Nd"(port)
    );
}

static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile(
        "inb %1,%0"
        :"=a"(ret)
        :"Nd"(port)
    );
    return ret;
}


void ata_wait()
{
    while(inb(0x1F7)&0x80);
}


void ata_read_sector(
uint32_t lba,
uint16_t *buffer
)
{

    ata_wait();


    outb(0x1F6,
    0xE0 | ((lba>>24)&0x0F));


    outb(0x1F2,1);

    outb(0x1F3,
    lba&0xff);

    outb(0x1F4,
    (lba>>8)&0xff);

    outb(0x1F5,
    (lba>>16)&0xff);


    outb(0x1F7,0x20);


    ata_wait();


    for(int i=0;i<256;i++)
    {
        buffer[i]=
        inw(0x1F0);
    }

}
