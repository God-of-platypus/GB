#include "instruction/16bitop.h"

void addr16(gameboy *gb, r16 r16) {
    uint16_t hl_value = get_value_hl(gb);
    uint16_t val = 0;
    switch (r16) {
        case af:
            val = get_value_af(gb);
            break;
        case bc:
            val = get_value_bc(gb);
            break;
        case de:
            val = get_value_de(gb);
            break;
        case hl:
            val = hl_value;
            break;
        default:
            return;
    }
    set_subtract_flag(gb, false);
    set_carry_flag(gb, val > 0xFFFF - hl_value);
    set_half_flag(gb, (val & 0xFFF) > 0xFFF - (hl_value & 0xFFF));
    set_zero_flag(gb, val + hl_value == 0);

    set_value_hl(gb, hl_value + val);
}

void decr16(gameboy *gb, r16 r16) {
    uint16_t val;
    switch (r16) {
        case af:
            val = get_value_af(gb);
            set_value_af(gb, val - 1);
            break;
        case bc:
            val = get_value_bc(gb);
            set_value_bc(gb, val - 1);
            break;
        case de:
            val = get_value_de(gb);
            set_value_de(gb, val - 1);
            break;
        case hl:
            val = get_value_hl(gb);
            set_value_hl(gb, val - 1);
            break;
        default:
            return;
    }
}
