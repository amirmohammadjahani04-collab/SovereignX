#include "memory.h"


static uint64_t heap =
    0x1000000;


void memory_init()
{
    heap = 0x1000000;
}


void* kmalloc(uint64_t size)
{

    void* addr =
        (void*)heap;


    heap += size;


    return addr;
}


void kfree(void* ptr)
{
    // نسخه اولیه
}
