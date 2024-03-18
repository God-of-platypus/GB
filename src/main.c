#include "instruction/register_intruction.h"

int main(void)
{
    gameboy *gb = make_gameboy();
    gb->reg[a] = 5;
    set_value_hl(gb, 0x1234);
    gb->memory[0x1234] = 3;
    andhl(gb);
    return 0;
}
