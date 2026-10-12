#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

void memory_init();

void* kmalloc(uint64_t size);

void kfree(void* ptr);

#endif
