

#include <stdint.h>


static inline uint8_t inb(
uint16_t port
)
{
    uint8_t ret;

    asm volatile(
    "inb %1,%0"
    :"=a"(ret)
    :"Nd"(port)
    );

    return ret;
}



void keyboard_handler()
{

    uint8_t scan =
        inb(0x60);


    // بعداً تبدیل به کاراکتر

}

