#include <stdint.h>

extern void draw_text(int x,int y,const char* text,uint32_t color);

void run_app(const char* name)
{
    draw_text(200,300,"Running SovereignX Application",0x00ff00);
    draw_text(200,330,name,0x00ff00);
}
