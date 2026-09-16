#include "gba_funcs.h"
#include "gba_colours.h"

struct obj_attribute oam_shadow[128];

void hw_sprite_update(void)
{
    volatile u32 *destination = (volatile u32 *)OVROM_ADDR;
    u32 *source = (u32 *)oam_shadow;

    for (int i = 0; i < (128 * sizeof(struct obj_attribute) >> 2); i++)
    {
        destination[i] = source[i];
    }
}

int main(void)
{
    REG_DISPCNT = MODE3 | BG2_ENABLE; /*| OBJ_ENABLE; */

    /* Don't mind these, these are just for test */
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