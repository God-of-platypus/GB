#pragma once

#include "register/register.h"

void adcr8(gameboy *gb, reg r);
void adchl(gameboy *gb);
void adcn8(gameboy *gb, uint8_t value);

void addr8(gameboy *gb, reg r);
void addhl(gameboy *gb);
void addn8(gameboy *gb, uint8_t value);

void andr8(gameboy *gb, reg r);
void andhl(gameboy *gb);
void andn8(gameboy *gb, uint8_t value);

void cpr8(gameboy *gb, reg r);
void cphl(gameboy *gb);
void cpn8(gameboy *gb, uint8_t value);

void decr8(gameboy *gb, reg r);
void dechl(gameboy *gb);

