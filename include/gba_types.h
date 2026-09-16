#ifndef GBA_TYPES_H
#define GBA_TYPES_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;

struct vec2_32
{
    s32 x;
    s32 y;
};

struct vec2_16
{
    s16 x;
    s16 y;
};

struct vec3_32
{
    s32 x;
    s32 y;
    s32 z;
};

struct vec3_16
{
    s16 x;
    s16 y;
    s16 z;
};

struct colour_vec
{
    s16 r;
    s16 g;
    s16 b;
};

#endif