#include <stdint.h>


uint64_t syscall_handler(
uint64_t id,
uint64_t arg
)
{

    switch(id)
    {

        case 1:

            // print

            return 1;


        case 2:

            // file open

            return 1;


    }


    return 0;

}

