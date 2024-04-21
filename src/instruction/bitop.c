#include "instruction/bitop.h"

void bitr8(gameboy *gb, reg r, uint8_t value)
{
    if (value > 7 || r < a || r > l)
    {
        return;
    }
    
    bool set = (gb->reg[r]  & (1 << value)) >> value;
    set_zero_flag(gb, !set);
    set_half_flag(gb, true);
    set_subtract_flag(gb, false);
}

void bithl(gameboy *gb, uint8_t value)
{
    if (value > 7)
    {
        return;
    }
    uint8_t v = gb->memory[get_value_hl(gb)];
    bool set = (v & (1 << value)) >> value;
    set_zero_flag(gb, !set);
    set_half_flag(gb, true);
    set_subtract_flag(gb, false);
}

void resr8(gameboy *gb, reg r, uint8_t value)
{
    if (value > 7 || r < a || r > l)
    {
        return;
    }
    gb->reg[r] &= ~(1 << value);
}

void reshl(gameboy *gb, uint8_t value)
{
    if (value > 7) {
        return;
    }
    gb->memory[get_value_hl(gb)] &= ~(1 << value);
}

void setr8(gameboy *gb, reg r, uint8_t value)
{
    if (value > 7 || r < a || r > l)
    {
        return;
    }
    gb->reg[r] |= (1 << value);
}

void sethl(gameboy *gb, uint8_t value)
{
    if (value > 7) {
        return;
    }
    gb->memory[get_value_hl(gb)] |= (1 << value);
}

void swapr8(gameboy *gb, reg r)
{
    if (r < a || r > l)
    {
        return;
    }
    gb->reg[r] = ((gb->reg[r] & 0xF0) >> 4) | ((gb->reg[r] & 0xF) << 4);
    set_subtract_flag(gb, false);
    set_half_flag(gb, false);
    set_carry_flag(gb, false);
    set_zero_flag(gb, gb->reg[r] == 0);
}

void swaphl(gameboy *gb)
{
    uint8_t value = gb->memory[get_value_hl(gb)];
    value = ((value & 0xF0) >> 4) | ((value & 0xF) << 4);
    set_subtract_flag(gb, false);
    set_half_flag(gb, false);
    set_carry_flag(gb, false);
    set_zero_flag(gb, value == 0);
    gb->memory[get_value_hl(gb)] = value;
}
