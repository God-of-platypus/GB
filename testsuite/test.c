#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "gameboy/gameboy.h"
#include "register/register.h"

Test(gameboy, builder_with_memory)
{
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    free_gameboy(gb);
    cr_assert(gb->sp == STACK_POINTER_DEFAULT);
    cr_assert(gb->pc == PROGRAM_COUNTER);
}

Test(register, set_af)
{
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    set_value_af(gb, 0xBEEF);
    cr_assert(gb->reg[a] == 0xBE);
    cr_assert(gb->reg[f] == 0xEF);
    free_gameboy(gb);
}

Test(register, set_bc)
{
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    set_value_bc(gb, 0xBEEF);
    cr_assert(gb->reg[b] == 0xBE);
    cr_assert(gb->reg[c] == 0xEF);
    free_gameboy(gb);
}

Test(register, set_de)
{
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    set_value_de(gb, 0xBEEF);
    cr_assert(gb->reg[d] == 0xBE);
    cr_assert(gb->reg[e] == 0xEF);
    free_gameboy(gb);
}

Test(register, set_hl)
{
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    set_value_hl(gb, 0xBEEF);
    cr_assert(gb->reg[h] == 0xBE);
    cr_assert(gb->reg[l] == 0xEF);
    free_gameboy(gb);
}

Test(register, get_af)
{
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    set_value_af(gb, 0xBEEF);
    uint16_t val = get_value_af(gb);
    cr_assert(val == 0xBEEF, "The value of af should be 0xBEEF and not 0x%04X",
              val);
    free_gameboy(gb);
}

Test(register, get_bc)
{
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    set_value_bc(gb, 0xBEEF);
    uint16_t val = get_value_bc(gb);
    cr_assert(val == 0xBEEF, "The value of bc should be 0xBEEF and not 0x%04X",
              val);
    free_gameboy(gb);
}

Test(register, get_de)
{
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    set_value_de(gb, 0xBEEF);
    uint16_t val = get_value_de(gb);
    cr_assert(val == 0xBEEF, "The value of de should be 0xBEEF and not 0x%04X",
              val);
    free_gameboy(gb);
}

Test(register, get_hl)
{
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    set_value_hl(gb, 0xBEEF);
    uint16_t val = get_value_hl(gb);
    cr_assert(val == 0xBEEF, "The value of bc should be 0xBEEF and not 0x%04X",
              val);
    free_gameboy(gb);
}

Test(register, set_zero_flag)
{
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    set_zero_flag(gb, true);
    cr_assert(gb->reg[f] == 0x80);
    free_gameboy(gb);
}

Test(register, get_zero_flag)
{
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    set_zero_flag(gb, true);
    cr_assert(get_zero_flag(gb));
    free_gameboy(gb);
}

Test(register, set_subtract)
{
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    set_subtract_flag(gb, true);
    cr_assert(gb->reg[f] == 0x40);
    free_gameboy(gb);
}

Test(register, get_subtract)
{
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    set_subtract_flag(gb, true);
    cr_assert(get_subtract_flag(gb));
    free_gameboy(gb);
}

Test(register, set_half)
{
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    set_half_flag(gb, true);
    cr_assert(gb->reg[f] == 0x20);
    free_gameboy(gb);
}

Test(register, get_half)
{
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    set_half_flag(gb, true);
    cr_assert(get_half_flag(gb));
    free_gameboy(gb);
}

Test(register, set_carry)
{
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    set_carry_flag(gb, true);
    cr_assert(gb->reg[f] == 0x10);
    free_gameboy(gb);
}

Test(register, get_carry)
{
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    set_carry_flag(gb, true);
    cr_assert(get_carry_flag(gb));
    free_gameboy(gb);
}
