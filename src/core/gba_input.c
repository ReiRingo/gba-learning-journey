#include "gba_input.h"
#include "gba_hw.h"

static u16 keys;
static u16 keys_prev;

void input_update(void)
{
    keys_prev = keys;
    keys = ~REG_KEYINPUT;
}

u16 input_held(u16 key)
{
    return keys & key;
}

u16 input_pressed(u16 key)
{
    return keys & ~keys_prev & key;
}

u16 key_released(u16 key)
{
    return ~keys & keys_prev & key;
}