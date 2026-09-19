#ifndef GBA_INPUT_H
#define GBA_INPUT_H

#include "gba_hw.h"

void input_update(void);
u16 input_held(u16);
u16 input_pressed(u16);
u16 key_released(u16);

#endif