#include "instruction/register_intruction.h"

int main(void)
{
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0xE;
    set_value_hl(gb, 0x1234);
    gb->memory[0x1234] = 0xF;
    cphl(gb);
    return 0;
}
