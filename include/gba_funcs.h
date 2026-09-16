#ifndef GBA_FUNCS_H
#define GBA_FUNCS_H

#include "gba_sprites.h"

static inline void vblank_wait(void)
{
    while (REG_VCOUNT >= 160);
    while (REG_VCOUNT < 160);
}

static inline u16 rgb(unsigned char r, unsigned char g, unsigned char b)
{
    return ((r >> 3)) | ((g >> 3) << 5) | ((b >> 3) << 10);
}

static inline struct colour_vec rgb15_vec3(u16 colour)
{
    return (struct colour_vec){
        .r =  colour        & 0x1F,
        .g = (colour >> 5)  & 0x1F,
        .b = (colour >> 10) & 0x1F
    };
}

static inline struct colour_vec rgb_vec3(u16 colour)
{
    u16 r =  colour & 0x1F;
    u16 g = (colour >> 5) & 0x1F;
    u16 b = (colour >> 10) & 0x1F;

    return (struct colour_vec){
        .r =  (r << 3) | (r >> 2),
        .g = (g << 3) | (g >> 2),
        .b = (b << 3) | (b >> 2)
    };
}

/** NOTE: This does NOT perform any bound checks */
static inline void pixel_put(s32 x, s32 y, u16 colour)
{
    VRAM[y * 240 + x] = colour;
}

void sprite_set_position(struct obj_attribute* sprite, s32 x, s32 y)
{
    sprite->attr0 = (sprite->attr0 & ~0x00FF) | (y & 0x00FF);
    sprite->attr1 = (sprite->attr1 & ~0x01FF) | (x & 0x01FF);
}

#endif