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