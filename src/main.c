#include "gba.h"
#include "p2.h"

int main(void)
{
    struct obj_attribute oam_entries[128];

    for (int i = 0; i < 128; i++)
    {
        oam_entries[i].attr0 = (2 << 8);
        oam_entries[i].attr1 = (2 << 14); 
        oam_entries[i].attr2 = 0;
    }

    oam_entries[0].attr0 = 50; 
    
    oam_entries[0].attr1 = 20 | (2 << 14); 
    
    oam_entries[0].attr2 = 0; 

    dma3_copy_32((const void *)p2Tiles, (void *)OBJ_VRAM, p2TilesLen >> 2);
    dma3_copy((const void *)p2Pal, (void *)OBJ_PALRAM, 16);

    REG_DISPCNT = MODE0 | OBJ_ENABLE | OBJ_1D_MAPPING;

    s32 x = 0;
    s32 y = 0;

    for (;;)
    {
        vblank_wait();
        dma3_copy_32((const void *)oam_entries, (void *)OVRAM, sizeof(oam_entries) >> 2);

        input_update();

        int speed = 1 + 1 * input_held(KEY_B);

        if (input_held(KEY_RIGHT) && x < 240 - 32)
        {
            x += speed;
        }
        if (input_held(KEY_LEFT) && x > 0)
        {
            x -= speed;
        }
        if (input_held(KEY_DOWN) && y < 160 - 32)
        {
            y += speed;
        }
        if (input_held(KEY_UP) && y > 0)
        {
            y -= speed;
        }

        sprite_set_position(&oam_entries[0], x, y);
    }

    return 0;
}