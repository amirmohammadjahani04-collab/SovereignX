#ifndef SYSCALL_H
#define SYSCALL_H

void syscall_init();

uint64_t syscall_handler(
uint64_t id,
uint64_t arg
);

#endif
