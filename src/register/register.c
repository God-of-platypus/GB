#include "register/register.h"

static void set_value_reg(gameboy *gb, uint16_t value, reg first, reg second)
{
    gb->reg[first] = ((value & 0xFF00) >> 8);
    gb->reg[second] = value & UINT8_MAX;
}

static uint16_t get_value_reg(gameboy *gb, reg first, reg second)
{
    return (gb->reg[first] << 8) + gb->reg[second];
}

void set_value_af(gameboy *gb, uint16_t value)
{
    set_value_reg(gb, value, a, f);
}

void set_value_bc(gameboy *gb, uint16_t value)
{
    set_value_reg(gb, value, b, c);
}

void set_value_de(gameboy *gb, uint16_t value)
{
    set_value_reg(gb, value, d, e);
}

void set_value_hl(gameboy *gb, uint16_t value)
{
    set_value_reg(gb, value, h, l);
}

uint16_t get_value_af(gameboy *gb)
{
    return get_value_reg(gb, a, f);
}

uint16_t get_value_bc(gameboy *gb)
{
    return get_value_reg(gb, b, c);
}

uint16_t get_value_de(gameboy *gb)
{
    return get_value_reg(gb, d, e);
}

uint16_t get_value_hl(gameboy *gb)
{
    return get_value_reg(gb, h, l);
}

void set_zero_flag(gameboy *gb, bool value)
{
    gb->reg[f] |= (value << ZERO_FLAG_POSITION);
}

bool get_zero_flag(gameboy *gb)
{
    return (gb->reg[f] & (1 << ZERO_FLAG_POSITION)) >> ZERO_FLAG_POSITION;
}

void set_subtract_flag(gameboy *gb, bool value)
{
    gb->reg[f] |= (value << SUBTRACT_FLAG_POSITION);
}

bool get_subtract_flag(gameboy *gb)
{
    return (gb->reg[f] & (1 << SUBTRACT_FLAG_POSITION))
        >> SUBTRACT_FLAG_POSITION;
}

void set_half_flag(gameboy *gb, bool value)
{
    gb->reg[f] |= (value << HALF_CARRY_FLAG_POSITION);
}

bool get_half_flag(gameboy *gb)
{
    return (gb->reg[f] & (1 << HALF_CARRY_FLAG_POSITION))
        >> HALF_CARRY_FLAG_POSITION;
}

void set_carry_flag(gameboy *gb, bool value)
{
    gb->reg[f] |= (value << CARRY_FLAG_POSITION);
}

bool get_carry_flag(gameboy *gb)
{
    return (gb->reg[f] & (1 << CARRY_FLAG_POSITION)) >> CARRY_FLAG_POSITION;
}
