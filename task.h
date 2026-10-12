#ifndef TASK_H
#define TASK_H

#include <stdint.h>

#define MAX_TASKS 4
#define STACK_SIZE 4096


struct task
{
    uint64_t id;

    uint64_t rsp;

    uint8_t stack[STACK_SIZE];

    int active;
};


void task_create(void (*entry)());

void schedule();

#endif
