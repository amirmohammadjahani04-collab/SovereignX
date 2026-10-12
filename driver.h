#ifndef DRIVER_H
#define DRIVER_H

struct driver
{
    char name[32];

    void (*init)();

};

void driver_register(struct driver d);

void drivers_init();

#endif
