#include "gba_funcs.h"
#include "gba_colours.h"

struct obj_attribute oam_shadow[128] = {0};

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
    REG_DISPCNT = MODE0 | OBJ_ENABLE | OBJ_1D_MAPPING;

    for (int i = 0; i < 128; i++)
    {
        oam_shadow[i].attr0 = (2 << 8);
        oam_shadow[i].attr1 = 0;
        oam_shadow[i].attr2 = 0;
    }

    oam_shadow[0].attr0 = 50;
    oam_shadow[0].attr1 = 100 | (1 << 14);
    oam_shadow[0].attr2 = 0;

    OBJ_PALRAM[1] = COL_RED;

    /* Note to self: u8 writes to OBJ_VRAM breaks the thing */
    for (int i = 0; i < 16 * 4; i++)
    {
        OBJ_VRAM[i] = 0x1111;
    }

    hw_sprite_update();

    for (;;)
    {
        vblank_wait();
    }

    return 0;
}