#pragma once

#include "register/register.h"

void bitr8(gameboy *gb, reg r, uint8_t value);
void bithl(gameboy *gb, uint8_t value);

void resr8(gameboy *gb, reg r, uint8_t value);
void reshl(gameboy *gb, uint8_t value);

void setr8(gameboy *gb, reg r, uint8_t value);
void sethl(gameboy *gb, uint8_t value);
