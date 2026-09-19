#define GBA_IMPLEMENT
#include "gba.h"

#include "p.h"

static inline void inputs(s32 *x, s32 *y, s32 *f, s32 ff)
{
    int speed = input_held(KEY_B) ? 2 : 1;

    static int timer = 0;
    timer++;

    if (~REG_KEYINPUT && timer & (1 << 3))
    {
        timer = 0;
        *f += 1;

        if (*f > ff)
            *f = 0;
    }

    if (input_held(KEY_RIGHT) && *x < 240 - 32)
    {
        *x += speed;
    }
    if (input_held(KEY_LEFT) && *x > 0)
    {
        *x -= speed;
    }
    if (input_held(KEY_DOWN) && *y < 160 - 32)
    {
        *y += speed;
    }
    if (input_held(KEY_UP) && *y > 0)
    {
        *y -= speed;
    }
}

int main(void)
{
    struct obj_attribute oam_entries[128];

    for (int i = 0; i < 128; i++)
    {
        oam_entries[i].attr0 = (2 << 8);
        oam_entries[i].attr1 = 2 << 14; 
        oam_entries[i].attr2 = 0;
    }

    oam_entries[0].attr0 = 50;
    oam_entries[0].attr1 = 20 | (2 << 14);
    oam_entries[0].attr2 = 0; // This is very broken for some reason...

    dma3_copy_32((const void *)pTiles, (void *)OBJ_VRAM, pTilesLen >> 2);
    dma3_copy((const void *)pPal, (void *)OBJ_PALRAM, pPalLen >> 1);

    REG_DISPCNT = MODE0 | OBJ_ENABLE | OBJ_1D_MAPPING;

    s32 x = 0;
    s32 y = 0;
    s32 f = 0;

    for (;;)
    {
        input_update();
        inputs(&x, &y, &f, 3);

        oam_entries[0].attr2 = f * 16;

        dma3_copy_32((const void *)oam_entries, (void *)OVRAM, sizeof(oam_entries) >> 2);

        vblank_wait();
        sprite_set_position(&oam_entries[0], x, y);
    }

    return 0;
}