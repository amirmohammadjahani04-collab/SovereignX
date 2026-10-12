#include "driver.h"

void keyboard_init();
void mouse_init();
void disk_init();


void drivers_init()
{
    keyboard_init();
    mouse_init();
    disk_init();
}
