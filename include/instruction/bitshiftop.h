#pragma once
#include "register/register.h"

void rlr8(gameboy *gb, reg r);
void rlhl(gameboy *gb);
void rla(gameboy *gb);

void rlcr8(gameboy *gb, reg r);
void rlchl(gameboy *gb);
void rlca(gameboy *gb);

void rrr8(gameboy *gb, reg r);
