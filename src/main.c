#include "gba_funcs.h"
#include "gba_colours.h"

int main(void)
{
    REG_DISPCNT = MODE3 | BG2_ENABLE;

    s32 x;
    s32 y;
    s32 w;
    s32 h;

    w = 20;
    h = 20;
    x = (240 >> 1) - (w >> 1);
    y = (160 >> 1) - (h >> 1);

    for (;;)
    {
        vblank_wait();

        static s32 old_x = 0;

        for (int yy = y; yy < y + h; yy++)
            for (int xx = old_x; xx < x; xx++)
                pixel_put(xx, yy, COL_BLACK);

        old_x = x;

        for (int yy = y; yy < y + h; yy++)
            for (int xx = x; xx < x + w; xx++)
                pixel_put(xx, yy, COL_RED);

        x++;

        if (x > 240)
            x = 0;
    }
}