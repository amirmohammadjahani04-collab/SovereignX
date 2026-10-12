
enum event_type
{
    CLICK,
    KEY
};


struct event
{
    int type;
    int x;
    int y;
};


struct event queue[64];

int event_pos=0;


void push_event(
struct event e
)
{
    queue[event_pos++]=e;
}


struct event get_event()
{
    return queue[0];
}

