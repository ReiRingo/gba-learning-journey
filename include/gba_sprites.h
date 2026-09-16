#ifndef GBA_SPR_H
#define GBA_SPR_H

#include "gba_hw.h"

struct obj_attribute
{
    u16 attr0;
    u16 attr1;
    u16 attr2;
    s16 fill;
} __attribute__((packed, aligned(4)));

#endif