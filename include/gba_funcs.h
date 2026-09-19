#ifndef GBA_FUNCS_H
#define GBA_FUNCS_H

#include "gba_hw.h"
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
        .r = colour & 0x1F,
        .g = (colour >> 5) & 0x1F,
        .b = (colour >> 10) & 0x1F
    };
}

static inline struct colour_vec rgb_vec3(u16 colour)
{
    u16 r = colour & 0x1F;
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

static inline void dma3_copy(const void *source, void *dest, u32 count)
{
    REG_DMA3_SAD = (u32)source;
    REG_DMA3_DAD = (u32)dest;
    REG_DMA3_CNT = count | (0 << 26) | (1 << 31); 

    while (REG_DMA3_CNT & (1 << 31));
}

static inline void dma3_fill(u16 value, void *dest, u32 count)
{
    static volatile u16 src_val;
    src_val = value;

    REG_DMA3_SAD = (u32)&src_val;
    REG_DMA3_DAD = (u32)dest;
    REG_DMA3_CNT = count | ((2 << 7 | 0 << 5 | 0 << 10 | 0 << 12 | 1 << 15) << 16);

    while (REG_DMA3_CNT & (1 << 31));
}

// --- 32-bit DMA3 (New) ---
static inline void dma3_copy_32(const void *source, void *dest, u32 count)
{
    REG_DMA3_SAD = (u32)source;
    REG_DMA3_DAD = (u32)dest;
    REG_DMA3_CNT = count | (1 << 26) | (1 << 31);

    while (REG_DMA3_CNT & (1 << 31));
}

static inline void dma3_fill_32(u32 value, void *dest, u32 count)
{
    static volatile u32 src_val;
    src_val = value;

    REG_DMA3_SAD = (u32)&src_val;
    REG_DMA3_DAD = (u32)dest;
    REG_DMA3_CNT = count | (1 << 26) | (0 << 9) | (1 << 31);

    while (REG_DMA3_CNT & (1 << 31));
}

static inline void screen_clear(u16 colour)
{
    u32 colour32 = colour | (colour << 16);
    dma3_fill_32(colour32, (void *)VRAM, (240 * 160) >> 1);
}

void sprite_set_position(struct obj_attribute* sprite, s32 x, s32 y)
{
    sprite->attr0 = (sprite->attr0 & ~0x00FF) | (y & 0x00FF);
    sprite->attr1 = (sprite->attr1 & ~0x01FF) | (x & 0x01FF);
}

#endif