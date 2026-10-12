#ifndef FS_H
#define FS_H

void fs_init();

int file_create(char* name);

int file_read(
char* name,
char* buffer
);

#endif
