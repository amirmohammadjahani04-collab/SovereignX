
#include "irq.h"


void timer_handler();
void keyboard_handler();


void irq0_handler()
{
    timer_handler();
}


void irq1_handler()
{
    keyboard_handler();
}

