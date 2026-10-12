#ifndef APP_FORMAT_H
#define APP_FORMAT_H

#define SOVEREIGNX_APP_MAGIC "MYAPP"

struct SovereignX_App
{
    char magic[6];
    char name[32];
    int version;
};

#endif
