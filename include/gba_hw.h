#ifndef GBA_HW_H
#define GBA_HW_H

/* -- Types -- */

#include "gba_types.h"


/* -- Memory Regions -- */

#define EWRAM   ((volatile u8 *)0x02000000)
#define IWRAM   ((volatile u8 *)0x03000000)
#define IO      ((volatile u8 *)0x04000000)
#define PALRAM  ((volatile u8 *)0x05000000)
#define VRAM    ((volatile u16 *)0x06000000)
#define OVRAM   ((volatile u8 *)0x07000000)
#define ROM     ((const volatile u8 *)0x08000000)
#define SRAM    ((volatile u8 *)0x0E000000)


/* -- Display -- */

#define REG_DISPCNT  (*(volatile u16 *)0x04000000)
#define REG_DISPSTAT (*(volatile u16 *)0x04000004)
#define REG_VCOUNT   (*(volatile u16 *)0x04000006)


/* -- Input -- */

#define REG_KEYINPUT (*(volatile u16 *)0x04000130)


/* -- Interrupts -- */

#define REG_IE       (*(volatile u16 *)0x04000200)
#define REG_IF       (*(volatile u16 *)0x04000202)
#define REG_IME      (*(volatile u16 *)0x04000208)


/* -- DMA 3 -- */

#define REG_DMA3_SAD (*(volatile u32 *)0x040000D4)
#define REG_DMA3_DAD (*(volatile u32 *)0x040000D8)
#define REG_DMA3_CNT (*(volatile u32 *)0x040000DC)


/* -- Display Modes -- */

#define MODE0        (0)
#define MODE1        (1)
#define MODE2        (2)
#define MODE3        (3)
#define MODE4        (4)
#define MODE5        (5)


/* -- BG On Bits -- */

#define BG0_ENABLE   (1 << 8)
#define BG1_ENABLE   (1 << 9)
#define BG2_ENABLE   (1 << 10)
#define BG3_ENABLE   (1 << 11)
#define OBJ_ENABLE   (1 << 12)


/* -- Colours -- */

#define RGB15(r, g, b) ((r) | ((g) << 5) | ((b) << 10))

#endif