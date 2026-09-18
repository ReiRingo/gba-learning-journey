#include "gba.h"

static IN_EWRAM u16 colour_white[240 * 160];
static IN_EWRAM u16 colour_black[240 * 160];

int main(void)
{
    REG_DISPCNT = MODE3 | BG2_ENABLE;

    for (int i = 0; i < 240 * 160; i++)
    {
        colour_white[i] = COL_WHITE;
        colour_black[i] = 0;
    }

    for (;;)
    {
        vblank_wait();
        input_update();

        if (input_pressed(KEY_A))
        {
            dma3_copy(colour_white, (void *)VRAM, 240 * 160);
        }
        if (input_pressed(KEY_B))
        {
            dma3_copy(colour_black, (void *)VRAM, 240 * 160);
        }
    }

    return 0;
}