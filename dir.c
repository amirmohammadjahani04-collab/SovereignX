#include "dir.h"

struct fat_dir_entry root[64];


int fat_search(
char *name,
struct fat_dir_entry *out
)
{

    for(int i=0;i<64;i++)
    {

        if(root[i].name[0]==name[0])
        {

            *out=root[i];

            return 1;

        }

    }


    return 0;

}

