#pragma once

#include <stdint.h>
#include <stdlib.h>

#define REGISTER_NUMBER 0x8
#define MEMORY_SIZE UINT16_MAX + 1
#define VRAM_START 0x8000
#define VRAM_SIZE 0x2000
#define STACK_POINTER_DEFAULT 0xFFFE
#define PROGRAM_COUNTER 0x100

typedef struct
{
    uint8_t *reg;
    uint8_t *memory;
    uint16_t pc;
    uint16_t sp;
} gameboy;

gameboy *make_gameboy(void);
void free_gameboy(gameboy *gb);

