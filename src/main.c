#include "gba_funcs.h"

int main(void)
{
    REG_DISPCNT = MODE3 | BG2_ENABLE;

    VRAM[(160 >> 1) * 240 + (240 >> 1)] = rgb(255, 0, 0);

    for (;;)
    {
        vblank_wait();
    }
}