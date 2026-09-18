#include "gba.h"

int main(void)
{
    REG_DISPCNT = MODE3 | BG2_ENABLE;

    for (;;)
    {
        vblank_wait();
        input_update();

        if (input_pressed(KEY_A))
        {
            screen_clear(COL_WHITE);
        }
        if (input_pressed(KEY_B))
        {
            screen_clear(COL_BLACK);
        }
    }

    return 0;
}