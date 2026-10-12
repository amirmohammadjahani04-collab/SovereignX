#include "filesystem.h"

struct file
{
    char name[32];
    int size;
    int sector;
};


struct file files[32];


void fs_init()
{

    for(int i=0;i<32;i++)
    {
        files[i].size=0;
    }

}


int file_create(char* name)
{

    for(int i=0;i<32;i++)
    {

        if(files[i].size==0)
        {

            int j=0;

            while(name[j])
            {
                files[i].name[j]=name[j];
                j++;
            }

            files[i].size=1;
            files[i].sector=i+10;

            return 1;
        }

    }

    return 0;

}



int file_read(
char* name,
char* buffer
)
{

    for(int i=0;i<32;i++)
    {

        int j=0;

        while(name[j]==files[i].name[j]
        && name[j])
        {
            j++;
        }


        if(name[j]==0)
        {
            buffer[0]='O';
            buffer[1]='K';
            return 1;
        }

    }


    return 0;

}
