#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>


struct process
{
    int pid;

    uint64_t rip;

    uint64_t rsp;

    uint64_t cr3;

    int privilege;

    int active;
};


void process_create();

#endif
