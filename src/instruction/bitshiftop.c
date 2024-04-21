#include "instruction/bitshiftop.h"
#include <sys/types.h>

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

