#ifndef GBA_H
#define GBA_H

#include "gba_funcs.h"
#include "gba_colours.h"

#define IN_EWRAM __attribute__((section(".ewram")))

enum DISPLAY_SIZE
{
    DISP_W = 240,
    DISP_H = 160
};

enum INPUT_KEYS
{
    KEY_A = 1 << 0,
    KEY_B = 1 << 1,
    KEY_SELECT = 1 << 2,
    KEY_START = 1 << 3,
    KEY_RIGHT = 1 << 4,
    KEY_LEFT = 1 << 5,
    KEY_UP = 1 << 6,
    KEY_DOWN = 1 << 7,
    KEY_R = 1 << 8,
    KEY_L = 1 << 9 
};

#endif