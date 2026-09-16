#include "gba.h"
#include "gba_colours.h"

struct obj_attribute oam_shadow[128] = {0};

void hw_sprite_update(void)
{
    dma3_copy(oam_shadow, (void *)OVRAM_ADDR, sizeof(oam_shadow) / sizeof(u16));
}

/* Made this by hand */
static const u8 slime[8 * 8] =
{
    0, 0, 1, 1, 1, 1, 0, 0,
    0, 1, 3, 3, 3, 3, 1, 0,
    1, 2, 2, 2, 2, 3, 3, 1,
    1, 2, 1, 2, 3, 1, 3, 1,
    1, 2, 1, 2, 3, 1, 3, 1,
    1, 2, 2, 2, 3, 3, 3, 1,
    0, 1, 3, 3, 3, 3, 1, 0,
    0, 0, 1, 1, 1, 1, 0, 0
};

static u8 slime_4bpp[32];

static void pack_sprite(void)
{
    /* What the heck I have to do this? */
    for (int i = 0; i < 64; i += 2)
    {
        slime_4bpp[i >> 1] = (slime[i] & 0xf) | ((slime[i + 1] & 0xf) << 4);
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

    oam_shadow[0].attr0 = 0;
    oam_shadow[0].attr1 = SPRITE_SIZE_8x8;
    oam_shadow[0].attr2 = 0;

    OBJ_PALRAM[1] = COL_WHITE;
    OBJ_PALRAM[2] = rgb(135, 255, 169);
    OBJ_PALRAM[3] = rgb(80, 211, 214);

    pack_sprite();

    dma3_copy((const void *)slime_4bpp, (void *)OBJ_VRAM, sizeof(slime_4bpp) / sizeof(u16));

    hw_sprite_update();

    s32 x = DISP_W >> 1;
    s32 y = DISP_H >> 1;

    for (;;)
    {
        vblank_wait();

        x++;

        oam_shadow[0].attr0 = (oam_shadow[0].attr0 & ~0x00ff) | (y & 0xff);
        oam_shadow[0].attr1 = (oam_shadow[0].attr1 & ~0x01ff) | (x & 0x1ff);

        if (x + 8 > DISP_W)
        {
            x = 0;
        }

        hw_sprite_update();
    }

    return 0;
}