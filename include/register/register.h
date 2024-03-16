#pragma once

#include <stdbool.h>

#include "gameboy/gameboy.h"

#define ZERO_FLAG_POSITION 7
#define SUBTRACT_FLAG_POSITION 6
#define HALF_CARRY_FLAG_POSITION 5
#define CARRY_FLAG_POSITION 4

typedef enum
{
    a = 0,
    b = 1,
    c = 2,
    d = 3,
    e = 4,
    f = 5,
    h = 6,
    l = 7,
} reg;

void set_value_af(gameboy *gb, uint16_t value);
void set_value_bc(gameboy *gb, uint16_t value);
void set_value_de(gameboy *gb, uint16_t value);
void set_value_hl(gameboy *gb, uint16_t value);

uint16_t get_value_af(gameboy *gb);
uint16_t get_value_bc(gameboy *gb);
uint16_t get_value_de(gameboy *gb);
uint16_t get_value_hl(gameboy *gb);

void set_zero_flag(gameboy *gb, bool value);
bool get_zero_flag(gameboy *gb);

void set_subtract_flag(gameboy *gb, bool value);
bool get_subtract_flag(gameboy *gb);

void set_half_flag(gameboy *gb, bool value);
bool get_half_flag(gameboy *gb);

void set_carry_flag(gameboy *gb, bool value);
bool get_carry_flag(gameboy *gb);
