
#include <stdint.h>


void switch_stack(
uint64_t **old,
uint64_t *new
)
{

    asm volatile(

    "mov %%rsp,(%0)"
    :
    :"r"(old)
    );


    asm volatile(

    "mov %0,%%rsp"
    :
    :"r"(new)

    );

}

