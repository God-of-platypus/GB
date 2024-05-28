#include "instruction/bitshiftop.h"

void rlr8(gameboy *gb, reg r)
{
    if (r > l || r < a)
    {
        return;
    }
    uint8_t c = get_carry_flag(gb);
    uint8_t s = (gb->reg[r] & (1 << 7)) >> 7;
    uint8_t value = (gb->reg[r] << 1) | c;

    set_carry_flag(gb, s == 1);
    set_half_flag(gb, false);
    set_subtract_flag(gb, false);
    set_zero_flag(gb, value == 0);

    gb->reg[r] = value;
}

void rlhl(gameboy *gb)
{
    uint16_t w = get_value_hl(gb);
    uint8_t c = get_carry_flag(gb);
    uint8_t s = (gb->memory[w] & (1 << 7)) >> 7;
    uint8_t value = (gb->memory[w] << 1) | c;

    set_zero_flag(gb, value == 0);
    set_subtract_flag(gb, false);
    set_half_flag(gb, false);
    set_carry_flag(gb, s == 1);

    gb->memory[w] = value;
}

void rla(gameboy *gb)
{
    uint8_t c = get_carry_flag(gb);
    uint8_t s = (gb->reg[a] & (1 << 7)) >> 7;
    uint8_t value = (gb->reg[a] << 1) | c;

    set_carry_flag(gb, s == 1);
    set_half_flag(gb, false);
    set_subtract_flag(gb, false);
    set_zero_flag(gb, false);

    gb->reg[a] = value;
}

void rlcr8(gameboy *gb, reg r)
{
    if (r > l || r < a)
    {
        return;
    }
    uint8_t s = (gb->reg[r] & (1 << 7)) >> 7;
    uint8_t value = (gb->reg[r] << 1) | s;

    set_carry_flag(gb, s == 1);
    set_half_flag(gb, false);
    set_subtract_flag(gb, false);
    set_zero_flag(gb, value == 0);

    gb->reg[r] = value;
}

void rlchl(gameboy *gb)
{
    uint16_t w = get_value_hl(gb);
    uint8_t s = (gb->memory[w] & (1 << 7)) >> 7;
    uint8_t value = (gb->memory[w] << 1) | s;

    set_zero_flag(gb, value == 0);
    set_subtract_flag(gb, false);
    set_half_flag(gb, false);
    set_carry_flag(gb, s == 1);

    gb->memory[w] = value;
}

void rlca(gameboy *gb)
{
    uint8_t s = (gb->reg[a] & (1 << 7)) >> 7;
    uint8_t value = (gb->reg[a] << 1) | s;

    set_carry_flag(gb, s == 1);
    set_half_flag(gb, false);
    set_subtract_flag(gb, false);
    set_zero_flag(gb, false);

    gb->reg[a] = value;
}

void rrr8(gameboy *gb, reg r)
{
    if (r > l || r < a)
    {
        return;
    }
    uint8_t c = get_carry_flag(gb);
    uint8_t s = gb->reg[r] & 0x1;
    uint8_t value = (gb->reg[r] >> 1 ) | (c << 7);

    set_carry_flag(gb, s == 1);
    set_half_flag(gb, false);
    set_subtract_flag(gb, false);
    set_zero_flag(gb, value == 0);

    gb->reg[r] = value;
}

void rrhl(gameboy *gb)
{
    uint16_t w = get_value_hl(gb);
    uint8_t c = get_carry_flag(gb);
    uint8_t s = (gb->memory[w] & 0x1);
    uint8_t value = (gb->memory[w] >> 1) | (c << 7);

    set_zero_flag(gb, value == 0);
    set_subtract_flag(gb, false);
    set_half_flag(gb, false);
    set_carry_flag(gb, s == 1);

    gb->memory[w] = value;
}

void rra(gameboy *gb)
{
    uint8_t c = get_carry_flag(gb);
    uint8_t s = (gb->reg[a] & 0x1);
    uint8_t value = (gb->reg[a] >> 1) | (c << 7);

    set_carry_flag(gb, s == 1);
    set_half_flag(gb, false);
    set_subtract_flag(gb, false);
    set_zero_flag(gb, false);

    gb->reg[a] = value;
}

void rrcr8(gameboy *gb, reg r)
{
    if (r > l || r < a)
    {
        return;
    }
    uint8_t s = (gb->reg[r] & 0x1);
    uint8_t value = (gb->reg[r] >> 1) | (s << 7);

    set_carry_flag(gb, s == 1);
    set_half_flag(gb, false);
    set_subtract_flag(gb, false);
    set_zero_flag(gb, value == 0);

    gb->reg[r] = value;
}
