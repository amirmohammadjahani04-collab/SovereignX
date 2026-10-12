

int current_task = 0;


void scheduler_tick()
{

    current_task++;


    if(current_task > 10)
        current_task=0;

}



void scheduler_init()
{

    current_task=0;

}

