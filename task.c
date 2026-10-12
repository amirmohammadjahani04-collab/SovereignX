#include "task.h"


struct task tasks[MAX_TASKS];

int task_count = 0;
int current_task = 0;


void task_create(void (*entry)())
{

    struct task *t =
        &tasks[task_count];


    t->id = task_count;


    uint64_t stack_top =
        (uint64_t)
        &t->stack[STACK_SIZE];


    stack_top -= sizeof(uint64_t);


    *((uint64_t*)stack_top)
        = (uint64_t)entry;


    t->rsp = stack_top;


    t->active = 1;


    task_count++;

}



void schedule()
{

    current_task++;

    if(current_task >= task_count)
        current_task = 0;

}

