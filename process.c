#include "process.h"


struct process table[16];


int next_pid=1;


void process_create()
{

    struct process *p =
        &table[next_pid];


    p->pid =
        next_pid;


    p->privilege = 3; // User Ring


    p->active=1;


    next_pid++;

}

