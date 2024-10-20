#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "gameboy/gameboy.h"
#include "instruction/register_intruction.h"
#include "register/register.h"
#include "instruction/16bitop.h"
#include "instruction/bitop.h"
#include "instruction/bitshiftop.h"

Test(gameboy, builder_with_memory) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    free_gameboy(gb);
    cr_assert(gb->sp == STACK_POINTER_DEFAULT);
    cr_assert(gb->pc == PROGRAM_COUNTER);
}

Test(register, set_af) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    set_value_af(gb, 0xBEEF);
    cr_assert(gb->reg[a] == 0xBE);
    cr_assert(gb->reg[f] == 0xEF);
    free_gameboy(gb);
}

Test(register, set_bc) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    set_value_bc(gb, 0xBEEF);
    cr_assert(gb->reg[b] == 0xBE);
    cr_assert(gb->reg[c] == 0xEF);
    free_gameboy(gb);
}

Test(register, set_de) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    set_value_de(gb, 0xBEEF);
    cr_assert(gb->reg[d] == 0xBE);
    cr_assert(gb->reg[e] == 0xEF);
    free_gameboy(gb);
}

Test(register, set_hl) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    set_value_hl(gb, 0xBEEF);
    cr_assert(gb->reg[h] == 0xBE);
    cr_assert(gb->reg[l] == 0xEF);
    free_gameboy(gb);
}

Test(register, get_af) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    set_value_af(gb, 0xBEEF);
    uint16_t val = get_value_af(gb);
    cr_assert(val == 0xBEEF, "The value of af should be 0xBEEF and not 0x%04X",
              val);
    free_gameboy(gb);
}

Test(register, get_bc) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    set_value_bc(gb, 0xBEEF);
    uint16_t val = get_value_bc(gb);
    cr_assert(val == 0xBEEF, "The value of bc should be 0xBEEF and not 0x%04X",
              val);
    free_gameboy(gb);
}

Test(register, get_de) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    set_value_de(gb, 0xBEEF);
    uint16_t val = get_value_de(gb);
    cr_assert(val == 0xBEEF, "The value of de should be 0xBEEF and not 0x%04X",
              val);
    free_gameboy(gb);
}

Test(register, get_hl) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    set_value_hl(gb, 0xBEEF);
    uint16_t val = get_value_hl(gb);
    cr_assert(val == 0xBEEF, "The value of bc should be 0xBEEF and not 0x%04X",
              val);
    free_gameboy(gb);
}

Test(register, set_zero_flag) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    set_zero_flag(gb, true);
    cr_assert(gb->reg[f] == 0x80);
    free_gameboy(gb);
}

Test(register, get_zero_flag) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    set_zero_flag(gb, true);
    cr_assert(get_zero_flag(gb));
    free_gameboy(gb);
}

Test(register, set_subtract) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    set_subtract_flag(gb, true);
    cr_assert(gb->reg[f] == 0x40);
    free_gameboy(gb);
}

Test(register, get_subtract) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    set_subtract_flag(gb, true);
    cr_assert(get_subtract_flag(gb));
    free_gameboy(gb);
}

Test(register, set_half) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    set_half_flag(gb, true);
    cr_assert(gb->reg[f] == 0x20);
    free_gameboy(gb);
}

Test(register, get_half) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    set_half_flag(gb, true);
    cr_assert(get_half_flag(gb));
    free_gameboy(gb);
}

Test(register, set_carry) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    set_carry_flag(gb, true);
    cr_assert(gb->reg[f] == 0x10);
    free_gameboy(gb);
}

Test(register, get_carry) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    set_carry_flag(gb, true);
    cr_assert(get_carry_flag(gb));
    free_gameboy(gb);
}

Test(adcr8, normal) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    gb->reg[a] = 0x11;
    adcr8(gb, b);
    cr_assert(gb->reg[a] == 0x11);
    cr_assert_not(get_carry_flag(gb));
    cr_assert_not(get_half_flag(gb));
    cr_assert_not(get_subtract_flag(gb));
    cr_assert_not(get_zero_flag(gb));
}

Test(adcr8, carry) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    gb->reg[a] = 0xFF;
    gb->reg[b] = 0x2;
    adcr8(gb, b);
    cr_assert(gb->reg[a] == 0x01);
    cr_assert(get_carry_flag(gb));
    cr_assert(get_half_flag(gb));
    cr_assert_not(get_subtract_flag(gb));
    cr_assert_not(get_zero_flag(gb));
}

Test(adcr8, half_carry) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL, "Memory errors");
    gb->reg[a] = 0xF;
    gb->reg[b] = 0x1;
    adcr8(gb, b);
    cr_assert(gb->reg[a] == 0x10,
              "The sum of 0xF and 0x1 should be 0x10 and not 0x%2X",
              gb->reg[a]);
    cr_assert_not(get_carry_flag(gb), "Carry error");
    cr_assert_not(get_subtract_flag(gb));
    cr_assert_not(get_zero_flag(gb));
    cr_assert(get_half_flag(gb), "Half Carry should be true");
}

Test(adcr8, zero) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    gb->reg[a] = 0;
    adcr8(gb, b);
    cr_assert(gb->reg[a] == 0);
    cr_assert_not(get_carry_flag(gb));
    cr_assert_not(get_half_flag(gb));
    cr_assert_not(get_subtract_flag(gb));
    cr_assert(get_zero_flag(gb));
}

Test(adcr8, add_with_carry) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    gb->reg[a] = 0x1;
    set_carry_flag(gb, true);
    adcr8(gb, b);
    cr_assert(gb->reg[a] == 0x2);
    cr_assert_not(get_half_flag(gb));
    cr_assert_not(get_subtract_flag(gb));
    cr_assert_not(get_zero_flag(gb));
    cr_assert_not(get_carry_flag(gb));
}

Test(adchl, normal) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);

    gb->reg[a] = 0x1;
    set_value_hl(gb, 0x1234);
    gb->memory[0x1234] = 0x2;

    adchl(gb);
    cr_assert(gb->reg[a] == 0x3);
    cr_assert_not(get_carry_flag(gb));
    cr_assert_not(get_zero_flag(gb));
    cr_assert_not(get_subtract_flag(gb));
    cr_assert_not(get_half_flag(gb));
}

Test(adchl, carry) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);

    gb->reg[a] = 0x2;
    set_value_hl(gb, 0x1234);
    gb->memory[0x1234] = 0xFF;

    adchl(gb);
    cr_assert(gb->reg[a] == 0x1);
    cr_assert(get_carry_flag(gb));
    cr_assert_not(get_zero_flag(gb));
    cr_assert_not(get_subtract_flag(gb));
    cr_assert(get_half_flag(gb));
}

Test(adchl, zero) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);

    gb->reg[a] = 0x0;
    set_value_hl(gb, 0x1234);
    gb->memory[0x1234] = 0x00;

    set_value_hl(gb, 0x1234);

    adchl(gb);
    cr_assert(gb->reg[a] == 0x0);
    cr_assert_not(get_carry_flag(gb));
    cr_assert(get_zero_flag(gb));
    cr_assert_not(get_subtract_flag(gb));
    cr_assert_not(get_half_flag(gb));
}

Test(adchl, half_carry) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);

    gb->reg[a] = 0x1;
    set_value_hl(gb, 0x1234);
    gb->memory[0x1234] = 0x0F;

    set_value_hl(gb, 0x1234);

    adchl(gb);
    cr_assert(gb->reg[a] == 0x10);
    cr_assert_not(get_carry_flag(gb));
    cr_assert_not(get_zero_flag(gb));
    cr_assert_not(get_subtract_flag(gb));
    cr_assert(get_half_flag(gb));
}

Test(adchl, add_with_carry) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);

    gb->reg[a] = 0x1;
    set_carry_flag(gb, true);
    set_value_hl(gb, 0x1234);
    gb->memory[0x1234] = 0x0F;

    set_value_hl(gb, 0x1234);

    adchl(gb);
    cr_assert(gb->reg[a] == 0x11);
    cr_assert_not(get_carry_flag(gb));
    cr_assert_not(get_zero_flag(gb));
    cr_assert_not(get_subtract_flag(gb));
    cr_assert(get_half_flag(gb));
}

Test(adcn8, normal) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);

    gb->reg[a] = 0x1;
    adcn8(gb, 0x2);

    cr_assert(gb->reg[a] == 0x3);
    cr_assert_not(get_carry_flag(gb));
    cr_assert_not(get_half_flag(gb));
    cr_assert_not(get_subtract_flag(gb));
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(adcn8, carry) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);

    gb->reg[a] = 0xFF;
    adcn8(gb, 0x2);

    cr_assert(gb->reg[a] == 0x1);
    cr_assert(get_carry_flag(gb));
    cr_assert(get_half_flag(gb));
    cr_assert_not(get_subtract_flag(gb));
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(adcn8, zero) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);

    gb->reg[a] = 0x0;
    adcn8(gb, 0x0);

    cr_assert(gb->reg[a] == 0x0);
    cr_assert_not(get_carry_flag(gb));
    cr_assert_not(get_half_flag(gb));
    cr_assert_not(get_subtract_flag(gb));
    cr_assert(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(adcn8, half_carry) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);

    gb->reg[a] = 0xF;
    adcn8(gb, 0x1);

    cr_assert(gb->reg[a] == 0x10);
    cr_assert_not(get_carry_flag(gb));
    cr_assert(get_half_flag(gb));
    cr_assert_not(get_subtract_flag(gb));
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(adcn8, with_carry) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);

    gb->reg[a] = 0x1;
    set_carry_flag(gb, true);
    adcn8(gb, 0x2);

    cr_assert(gb->reg[a] == 0x4);
    cr_assert_not(get_carry_flag(gb));
    cr_assert_not(get_half_flag(gb));
    cr_assert_not(get_subtract_flag(gb));
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(addr8, normal) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    gb->reg[a] = 0x11;
    addr8(gb, b);
    cr_assert(gb->reg[a] == 0x11);
    cr_assert_not(get_carry_flag(gb));
    cr_assert_not(get_half_flag(gb));
    cr_assert_not(get_subtract_flag(gb));
    cr_assert_not(get_zero_flag(gb));
}

Test(addr8, carry) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    gb->reg[a] = 0xFF;
    gb->reg[b] = 0x2;
    addr8(gb, b);
    cr_assert(gb->reg[a] == 0x01);
    cr_assert(get_carry_flag(gb));
    cr_assert(get_half_flag(gb));
    cr_assert_not(get_subtract_flag(gb));
    cr_assert_not(get_zero_flag(gb));
}

Test(addr8, half_carry) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL, "Memory errors");
    gb->reg[a] = 0xF;
    gb->reg[b] = 0x1;
    addr8(gb, b);
    cr_assert(gb->reg[a] == 0x10,
              "The sum of 0xF and 0x1 should be 0x10 and not 0x%2X",
              gb->reg[a]);
    cr_assert_not(get_carry_flag(gb), "Carry error");
    cr_assert_not(get_subtract_flag(gb));
    cr_assert_not(get_zero_flag(gb));
    cr_assert(get_half_flag(gb), "Half Carry should be true");
}

Test(addr8, zero) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    gb->reg[a] = 0;
    addr8(gb, b);
    cr_assert(gb->reg[a] == 0);
    cr_assert_not(get_carry_flag(gb));
    cr_assert_not(get_half_flag(gb));
    cr_assert_not(get_subtract_flag(gb));
    cr_assert(get_zero_flag(gb));
}

Test(addhl, normal) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);

    gb->reg[a] = 0x1;
    set_value_hl(gb, 0x1234);
    gb->memory[0x1234] = 0x2;

    addhl(gb);
    cr_assert(gb->reg[a] == 0x3);
    cr_assert_not(get_carry_flag(gb));
    cr_assert_not(get_zero_flag(gb));
    cr_assert_not(get_subtract_flag(gb));
    cr_assert_not(get_half_flag(gb));
}

Test(addhl, carry) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);

    gb->reg[a] = 0x2;
    set_value_hl(gb, 0x1234);
    gb->memory[0x1234] = 0xFF;

    addhl(gb);
    cr_assert(gb->reg[a] == 0x1);
    cr_assert(get_carry_flag(gb));
    cr_assert_not(get_zero_flag(gb));
    cr_assert_not(get_subtract_flag(gb));
    cr_assert(get_half_flag(gb));
}

Test(addhl, zero) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);

    gb->reg[a] = 0x0;
    set_value_hl(gb, 0x1234);
    gb->memory[0x1234] = 0x00;

    set_value_hl(gb, 0x1234);

    addhl(gb);
    cr_assert(gb->reg[a] == 0x0);
    cr_assert_not(get_carry_flag(gb));
    cr_assert(get_zero_flag(gb));
    cr_assert_not(get_subtract_flag(gb));
    cr_assert_not(get_half_flag(gb));
}

Test(addhl, half_carry) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);

    gb->reg[a] = 0x1;
    set_value_hl(gb, 0x1234);
    gb->memory[0x1234] = 0x0F;

    set_value_hl(gb, 0x1234);

    addhl(gb);
    cr_assert(gb->reg[a] == 0x10);
    cr_assert_not(get_carry_flag(gb));
    cr_assert_not(get_zero_flag(gb));
    cr_assert_not(get_subtract_flag(gb));
    cr_assert(get_half_flag(gb));
}

Test(addn8, normal) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);

    gb->reg[a] = 0x1;
    addn8(gb, 0x2);

    cr_assert(gb->reg[a] == 0x3);
    cr_assert_not(get_carry_flag(gb));
    cr_assert_not(get_half_flag(gb));
    cr_assert_not(get_subtract_flag(gb));
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(addn8, carry) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);

    gb->reg[a] = 0xFF;
    addn8(gb, 0x2);

    cr_assert(gb->reg[a] == 0x1);
    cr_assert(get_carry_flag(gb));
    cr_assert(get_half_flag(gb));
    cr_assert_not(get_subtract_flag(gb));
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(addn8, zero) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);

    gb->reg[a] = 0x0;
    addn8(gb, 0x0);

    cr_assert(gb->reg[a] == 0x0);
    cr_assert_not(get_carry_flag(gb));
    cr_assert_not(get_half_flag(gb));
    cr_assert_not(get_subtract_flag(gb));
    cr_assert(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(addn8, half_carry) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);

    gb->reg[a] = 0xF;
    addn8(gb, 0x1);

    cr_assert(gb->reg[a] == 0x10);
    cr_assert_not(get_carry_flag(gb));
    cr_assert(get_half_flag(gb));
    cr_assert_not(get_subtract_flag(gb));
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(andr8, normal) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);

    gb->reg[a] = 5;
    gb->reg[b] = 3;

    andr8(gb, b);
    cr_assert(gb->reg[a] == 1);
    cr_assert_not(get_carry_flag(gb));
    cr_assert(get_half_flag(gb));
    cr_assert_not(get_zero_flag(gb));
    cr_assert_not(get_subtract_flag(gb));

    free_gameboy(gb);
}

Test(andr8, zero) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);

    gb->reg[a] = 8;
    gb->reg[b] = 3;

    andr8(gb, b);
    cr_assert(gb->reg[a] == 0);
    cr_assert_not(get_carry_flag(gb));
    cr_assert(get_half_flag(gb));
    cr_assert(get_zero_flag(gb));
    cr_assert_not(get_subtract_flag(gb));

    free_gameboy(gb);
}

Test(andhl, normal) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);

    gb->reg[a] = 0x5;
    set_value_hl(gb, 0x1234);
    gb->memory[0x1234] = 0x3;

    andhl(gb);
    cr_assert(gb->reg[a] == 0x1, "The value of gb->reg[a] is : %2X",
              gb->reg[a]);
    cr_assert_not(get_carry_flag(gb));
    cr_assert(get_half_flag(gb));
    cr_assert_not(get_zero_flag(gb));
    cr_assert_not(get_subtract_flag(gb));

    free_gameboy(gb);
}

Test(andhl, zero) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);

    gb->reg[a] = 0x8;
    set_value_hl(gb, 0x1234);
    gb->memory[0x1234] = 0x6;

    andhl(gb);
    cr_assert(gb->reg[a] == 0x0, "The value of gb->reg[a] is : %2X",
              gb->reg[a]);
    cr_assert_not(get_carry_flag(gb));
    cr_assert(get_half_flag(gb));
    cr_assert(get_zero_flag(gb));
    cr_assert_not(get_subtract_flag(gb));

    free_gameboy(gb);
}

Test(andn8, normal) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);

    gb->reg[a] = 0x5;

    andn8(gb, 0x3);
    cr_assert(gb->reg[a] == 0x1, "The value of gb->reg[a] is : %2X",
              gb->reg[a]);
    cr_assert_not(get_carry_flag(gb));
    cr_assert(get_half_flag(gb));
    cr_assert_not(get_zero_flag(gb));
    cr_assert_not(get_subtract_flag(gb));

    free_gameboy(gb);
}

Test(andn8, zero) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);

    gb->reg[a] = 0x8;

    andn8(gb, 0x7);
    cr_assert(gb->reg[a] == 0x0, "The value of gb->reg[a] is : %2X",
              gb->reg[a]);
    cr_assert_not(get_carry_flag(gb));
    cr_assert(get_half_flag(gb));
    cr_assert(get_zero_flag(gb));
    cr_assert_not(get_subtract_flag(gb));

    free_gameboy(gb);
}

Test(cpr8, normal) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);

    gb->reg[a] = 0xFF;
    gb->reg[b] = 0x01;

    cpr8(gb, b);
    cr_assert(get_subtract_flag(gb));
    cr_assert_not(get_carry_flag(gb));
    cr_assert_not(get_half_flag(gb));
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(cpr8, zero) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);

    gb->reg[a] = 0x01;
    gb->reg[b] = 0x01;

    cpr8(gb, b);
    cr_assert(get_subtract_flag(gb));
    cr_assert_not(get_carry_flag(gb));
    cr_assert_not(get_half_flag(gb));
    cr_assert(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(cpr8, carry) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);

    gb->reg[a] = 0xF;
    gb->reg[b] = 0x1F;

    cpr8(gb, b);
    cr_assert(get_subtract_flag(gb));
    cr_assert(get_carry_flag(gb), "F");
    cr_assert_not(get_half_flag(gb), "FF");
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(cpr8, half_carry) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);

    gb->reg[a] = 0xE;
    gb->reg[b] = 0xF;

    cpr8(gb, b);
    cr_assert(get_subtract_flag(gb));
    cr_assert(get_carry_flag(gb), "F");
    cr_assert(get_half_flag(gb), "FF");
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(cphl, normal) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);

    gb->reg[a] = 0xFF;
    set_value_hl(gb, 0x1234);
    gb->memory[0x1234] = 0x1;

    cphl(gb);
    cr_assert(get_subtract_flag(gb));
    cr_assert_not(get_carry_flag(gb));
    cr_assert_not(get_half_flag(gb));
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(cphl, zero) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);

    gb->reg[a] = 0x1;
    set_value_hl(gb, 0x1234);
    gb->memory[0x1234] = 0x1;

    cphl(gb);
    cr_assert(get_subtract_flag(gb));
    cr_assert_not(get_carry_flag(gb));
    cr_assert_not(get_half_flag(gb));
    cr_assert(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(cphl, carry) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);

    gb->reg[a] = 0xF;
    set_value_hl(gb, 0x1234);
    gb->memory[0x1234] = 0x1F;

    cphl(gb);
    cr_assert(get_subtract_flag(gb));
    cr_assert(get_carry_flag(gb), "F");
    cr_assert_not(get_half_flag(gb), "FF");
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(cphl, half_carry) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);

    gb->reg[a] = 0xE;
    set_value_hl(gb, 0x1234);
    gb->memory[0x1234] = 0xF;

    cphl(gb);
    cr_assert(get_subtract_flag(gb));
    cr_assert(get_carry_flag(gb), "F");
    cr_assert(get_half_flag(gb), "FF");
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(cpn8, normal) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);

    gb->reg[a] = 0xFF;

    cpn8(gb, 0x1);
    cr_assert(get_subtract_flag(gb));
    cr_assert_not(get_carry_flag(gb));
    cr_assert_not(get_half_flag(gb));
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(cpn8, zero) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);

    gb->reg[a] = 0x1;

    cpn8(gb, 0x1);
    cr_assert(get_subtract_flag(gb));
    cr_assert_not(get_carry_flag(gb));
    cr_assert_not(get_half_flag(gb));
    cr_assert(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(cpn8, carry) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);

    gb->reg[a] = 0xF;

    cpn8(gb, 0x1F);
    cr_assert(get_subtract_flag(gb));
    cr_assert(get_carry_flag(gb), "F");
    cr_assert_not(get_half_flag(gb), "FF");
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(cpn8, half_carry) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);

    gb->reg[a] = 0xE;

    cpn8(gb, 0xF);
    cr_assert(get_subtract_flag(gb));
    cr_assert(get_carry_flag(gb), "F");
    cr_assert(get_half_flag(gb), "FF");
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(decr8, normal) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);

    gb->reg[a] = 0xF;

    decr8(gb, a);
    cr_assert(gb->reg[a] == 0xE);
    cr_assert_not(get_zero_flag(gb));
    cr_assert_not(get_half_flag(gb));
    cr_assert(get_subtract_flag(gb));

    free_gameboy(gb);
}

Test(decr8, zero_flag) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);

    gb->reg[a] = 0x1;

    decr8(gb, a);
    cr_assert(gb->reg[a] == 0x0);
    cr_assert(get_zero_flag(gb));
    cr_assert_not(get_half_flag(gb));
    cr_assert(get_subtract_flag(gb));

    free_gameboy(gb);
}

Test(decr8, half) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);

    gb->reg[a] = 0x10;

    decr8(gb, a);
    cr_assert(gb->reg[a] == 0xF);
    cr_assert_not(get_zero_flag(gb));
    cr_assert(get_half_flag(gb));
    cr_assert(get_subtract_flag(gb));

    free_gameboy(gb);
}

Test(decr8, underflow) {
    gameboy *gb = make_gameboy();

    gb->reg[a] = 0x0;

    decr8(gb, a);

    cr_assert(gb->reg[a] == 0xFF);
    cr_assert_not(get_zero_flag(gb));
    cr_assert(get_half_flag(gb));
    cr_assert(get_subtract_flag(gb));

    free_gameboy(gb);
}

Test(dechl, normal) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    set_value_hl(gb, 0x1234);
    gb->memory[0x1234] = 0xF;
    dechl(gb);

    cr_assert(gb->memory[0x1234] == 0xE);
    cr_assert_not(get_zero_flag(gb));
    cr_assert_not(get_half_flag(gb));
    cr_assert(get_subtract_flag(gb));

    free_gameboy(gb);
}

Test(dechl, zero_flag) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    set_value_hl(gb, 0x1234);
    gb->memory[0x1234] = 0x1;

    dechl(gb);
    cr_assert(gb->memory[0x1234] == 0x0);
    cr_assert(get_zero_flag(gb));
    cr_assert_not(get_half_flag(gb));
    cr_assert(get_subtract_flag(gb));

    free_gameboy(gb);
}

Test(dechl, half) {
    gameboy *gb = make_gameboy();
    cr_assert(gb != NULL);
    set_value_hl(gb, 0x1234);
    gb->memory[0x1234] = 0x10;

    dechl(gb);
    cr_assert(gb->memory[0x1234] == 0xF);
    cr_assert_not(get_zero_flag(gb));
    cr_assert(get_half_flag(gb));
    cr_assert(get_subtract_flag(gb));

    free_gameboy(gb);
}

Test(dechl, underflow) {
    gameboy *gb = make_gameboy();
    set_value_hl(gb, 0x1234);
    gb->memory[0x1234] = 0x0;

    dechl(gb);
    cr_assert(gb->memory[0x1234] == 0xFF);
    cr_assert_not(get_zero_flag(gb));
    cr_assert(get_half_flag(gb));
    cr_assert(get_subtract_flag(gb));

    free_gameboy(gb);
}

Test(incr8, normal) {
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0x5;

    incr8(gb, a);

    cr_assert(gb->reg[a] == 0x6);
    cr_assert_not(get_zero_flag(gb));
    cr_assert_not(get_half_flag(gb));
    cr_assert_not(get_carry_flag(gb));

    free_gameboy(gb);
}

Test(incr8, half) {
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0xF;

    incr8(gb, a);

    cr_assert(gb->reg[a] == 0x10);
    cr_assert_not(get_carry_flag(gb));
    cr_assert(get_half_flag(gb));
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(incr8, overflow) {
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0xFF;

    incr8(gb, a);

    cr_assert(gb->reg[a] == 0x0);
    cr_assert(get_zero_flag(gb));
    cr_assert(get_half_flag(gb));
    cr_assert(get_carry_flag(gb));

    free_gameboy(gb);
}

Test(inchl, normal) {
    gameboy *gb = make_gameboy();
    set_value_hl(gb, 0x1234);
    gb->memory[0x1234] = 0xE;

    inchl(gb);

    cr_assert(gb->memory[0x1234] == 0xF);
    cr_assert_not(get_carry_flag(gb));
    cr_assert_not(get_half_flag(gb));
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(inchl, half) {
    gameboy *gb = make_gameboy();
    set_value_hl(gb, 0x1234);
    gb->memory[0x1234] = 0xF;

    inchl(gb);

    cr_assert(gb->memory[0x1234] == 0x10);
    cr_assert_not(get_carry_flag(gb));
    cr_assert(get_half_flag(gb));
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(inchl, overflow) {
    gameboy *gb = make_gameboy();
    set_value_hl(gb, 0x1234);
    gb->memory[0x1234] = 0xFF;

    inchl(gb);

    cr_assert(gb->memory[0x1234] == 0x0);
    cr_assert(get_carry_flag(gb));
    cr_assert(get_half_flag(gb));
    cr_assert(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(orr8, normal) {
    gameboy *gb = make_gameboy();
    gb->reg[b] = 0xF;
    gb->reg[a] = 0x8;

    orr8(gb, b);

    cr_assert(gb->reg[a] == 0x8);
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(orr8, zero) {
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0xFF;
    gb->reg[b] = 0x0;

    orr8(gb, b);

    cr_assert(gb->reg[a] == 0x0);
    cr_assert(get_zero_flag(gb));
    free_gameboy(gb);
}

Test(orhl, normal) {
    gameboy *gb = make_gameboy();
    gb->memory[0x1234] = 0xF8;
    set_value_hl(gb, 0x1234);

    gb->reg[a] = 0x8;

    orhl(gb);

    cr_assert(gb->reg[a] == 0x8);
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(orhl, zero) {
    gameboy *gb = make_gameboy();
    gb->memory[0x1234] = 0xF0;
    gb->reg[a] = 0xF;
    set_value_hl(gb, 0x1234);

    orhl(gb);

    cr_assert(gb->reg[a] == 0x0);
    cr_assert(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(orn8, normal) {
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0xF8;
    orn8(gb, 0x8);

    cr_assert(gb->reg[a] == 0x8);
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(orn8, zero) {
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0xF0;
    orn8(gb, 0xF);

    cr_assert(gb->reg[a] == 0x0);
    cr_assert(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(sbcr8, normal) {
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0xF2;
    gb->reg[b] = 0x1;

    sbcr8(gb, b);

    cr_assert(gb->reg[a] == 0xF1);
    cr_assert(get_subtract_flag(gb));
    cr_assert_not(get_zero_flag(gb));
    cr_assert_not(get_half_flag(gb));
    cr_assert_not(get_carry_flag(gb));

    free_gameboy(gb);
}

Test(sbcr8, with_carry) {
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0xF;
    gb->reg[b] = 0x1;
    set_carry_flag(gb, true);

    sbcr8(gb, b);

    cr_assert(gb->reg[a] == 0xD);
    cr_assert(get_subtract_flag(gb));
    cr_assert_not(get_carry_flag(gb));
    cr_assert_not(get_half_flag(gb));
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(sbcr8, half_carry) {
    gameboy *gb = make_gameboy();

    gb->reg[a] = 0x1E;
    gb->reg[b] = 0xF;

    sbcr8(gb, b);

    cr_assert(gb->reg[a] == 0xF, "Math is hard");
    cr_assert(get_subtract_flag(gb), "What the fuck");
    cr_assert_not(get_carry_flag(gb), "WTH");
    cr_assert(get_half_flag(gb));
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(sbcr8, zero) {
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0x1;
    gb->reg[b] = 0x1;

    sbcr8(gb, b);

    cr_assert(gb->reg[a] == 0x0);
    cr_assert(get_subtract_flag(gb));
    cr_assert(get_zero_flag(gb));
    cr_assert_not(get_half_flag(gb));
    cr_assert_not(get_carry_flag(gb));

    free_gameboy(gb);
}

Test(sbcr8, carry) {
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0xF;
    gb->reg[b] = 0x10;

    sbcr8(gb, b);

    cr_assert(gb->reg[a] == 0xFF);
    cr_assert(get_carry_flag(gb));
    cr_assert_not(get_half_flag(gb), "Maybe");
    cr_assert(get_subtract_flag(gb));
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(sbchl, normal) {
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0xF2;
    gb->memory[0x1234] = 0x1;
    set_value_hl(gb, 0x1234);
    sbchl(gb);

    cr_assert(gb->reg[a] == 0xF1);
    cr_assert(get_subtract_flag(gb));
    cr_assert_not(get_zero_flag(gb));
    cr_assert_not(get_half_flag(gb));
    cr_assert_not(get_carry_flag(gb));

    free_gameboy(gb);
}

Test(sbchl, with_carry) {
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0xF;
    gb->memory[0x1234] = 0x1;
    set_value_hl(gb, 0x1234);
    set_carry_flag(gb, true);

    sbchl(gb);

    cr_assert(gb->reg[a] == 0xD);
    cr_assert(get_subtract_flag(gb));
    cr_assert_not(get_carry_flag(gb));
    cr_assert_not(get_half_flag(gb));
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(sbchl, half_carry) {
    gameboy *gb = make_gameboy();

    gb->reg[a] = 0x1E;
    gb->memory[0x1234] = 0xF;
    set_value_hl(gb, 0x1234);

    sbchl(gb);

    cr_assert(gb->reg[a] == 0xF, "Math is hard");
    cr_assert(get_subtract_flag(gb), "What the fuck");
    cr_assert_not(get_carry_flag(gb), "WTH");
    cr_assert(get_half_flag(gb));
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(sbchl, zero) {
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0x1;
    gb->memory[0x1234] = 0x1;
    set_value_hl(gb, 0x1234);

    sbchl(gb);

    cr_assert(gb->reg[a] == 0x0);
    cr_assert(get_subtract_flag(gb));
    cr_assert(get_zero_flag(gb));
    cr_assert_not(get_half_flag(gb));
    cr_assert_not(get_carry_flag(gb));

    free_gameboy(gb);
}

Test(sbchl, carry) {
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0xF;
    gb->memory[0x1234] = 0x10;
    set_value_hl(gb, 0x1234);

    sbchl(gb);

    cr_assert(gb->reg[a] == 0xFF);
    cr_assert(get_carry_flag(gb));
    cr_assert_not(get_half_flag(gb), "Maybe");
    cr_assert(get_subtract_flag(gb));
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(sbcn8, normal) {
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0xF2;
    sbcn8(gb, 1);

    cr_assert(gb->reg[a] == 0xF1);
    cr_assert(get_subtract_flag(gb));
    cr_assert_not(get_zero_flag(gb));
    cr_assert_not(get_half_flag(gb));
    cr_assert_not(get_carry_flag(gb));

    free_gameboy(gb);
}

Test(sbcn8, with_carry) {
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0xF;
    set_carry_flag(gb, true);

    sbcn8(gb, 1);

    cr_assert(gb->reg[a] == 0xD);
    cr_assert(get_subtract_flag(gb));
    cr_assert_not(get_carry_flag(gb));
    cr_assert_not(get_half_flag(gb));
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(sbcn8, half_carry) {
    gameboy *gb = make_gameboy();

    gb->reg[a] = 0x1E;

    sbcn8(gb, 0xF);

    cr_assert(gb->reg[a] == 0xF, "Math is hard");
    cr_assert(get_subtract_flag(gb), "What the fuck");
    cr_assert_not(get_carry_flag(gb), "WTH");
    cr_assert(get_half_flag(gb));
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(sbcn8, zero) {
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0x1;

    sbcn8(gb, 0x1);

    cr_assert(gb->reg[a] == 0x0);
    cr_assert(get_subtract_flag(gb));
    cr_assert(get_zero_flag(gb));
    cr_assert_not(get_half_flag(gb));
    cr_assert_not(get_carry_flag(gb));

    free_gameboy(gb);
}

Test(sbcn8, carry) {
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0xF;

    sbcn8(gb, 0x10);

    cr_assert(gb->reg[a] == 0xFF);
    cr_assert(get_carry_flag(gb));
    cr_assert_not(get_half_flag(gb), "Maybe");
    cr_assert(get_subtract_flag(gb));
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(subr8, normal) {
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0xF2;
    gb->reg[b] = 0x1;

    subr8(gb, b);

    cr_assert(gb->reg[a] == 0xF1);
    cr_assert(get_subtract_flag(gb));
    cr_assert_not(get_zero_flag(gb));
    cr_assert_not(get_half_flag(gb));
    cr_assert_not(get_carry_flag(gb));

    free_gameboy(gb);
}

Test(subr8, half_carry) {
    gameboy *gb = make_gameboy();

    gb->reg[a] = 0x1E;
    gb->reg[b] = 0xF;

    subr8(gb, b);

    cr_assert(gb->reg[a] == 0xF, "Math is hard");
    cr_assert(get_subtract_flag(gb), "What the fuck");
    cr_assert_not(get_carry_flag(gb), "WTH");
    cr_assert(get_half_flag(gb));
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(subr8, zero) {
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0x1;
    gb->reg[b] = 0x1;

    subr8(gb, b);

    cr_assert(gb->reg[a] == 0x0);
    cr_assert(get_subtract_flag(gb));
    cr_assert(get_zero_flag(gb));
    cr_assert_not(get_half_flag(gb));
    cr_assert_not(get_carry_flag(gb));

    free_gameboy(gb);
}

Test(subr8, carry) {
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0xF;
    gb->reg[b] = 0x10;

    subr8(gb, b);

    cr_assert(gb->reg[a] == 0xFF);
    cr_assert(get_carry_flag(gb));
    cr_assert_not(get_half_flag(gb), "Maybe");
    cr_assert(get_subtract_flag(gb));
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(subhl, normal) {
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0xF2;
    gb->memory[0x1234] = 0x1;
    set_value_hl(gb, 0x1234);

    subhl(gb);

    cr_assert(gb->reg[a] == 0xF1);
    cr_assert(get_subtract_flag(gb));
    cr_assert_not(get_zero_flag(gb));
    cr_assert_not(get_half_flag(gb));
    cr_assert_not(get_carry_flag(gb));

    free_gameboy(gb);
}

Test(subhl, half_carry) {
    gameboy *gb = make_gameboy();

    gb->reg[a] = 0x1E;
    gb->memory[0x1234] = 0xF;
    set_value_hl(gb, 0x1234);

    subhl(gb);

    cr_assert(gb->reg[a] == 0xF, "Math is hard");
    cr_assert(get_subtract_flag(gb), "What the fuck");
    cr_assert_not(get_carry_flag(gb), "WTH");
    cr_assert(get_half_flag(gb));
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(subhl, zero) {
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0x1;
    gb->memory[0x1234] = 0x1;
    set_value_hl(gb, 0x1234);

    subhl(gb);

    cr_assert(gb->reg[a] == 0x0);
    cr_assert(get_subtract_flag(gb));
    cr_assert(get_zero_flag(gb));
    cr_assert_not(get_half_flag(gb));
    cr_assert_not(get_carry_flag(gb));

    free_gameboy(gb);
}

Test(subhl, carry) {
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0xF;
    gb->memory[0x1234] = 0x10;
    set_value_hl(gb, 0x1234);

    subhl(gb);

    cr_assert(gb->reg[a] == 0xFF);
    cr_assert(get_carry_flag(gb));
    cr_assert_not(get_half_flag(gb), "Maybe");
    cr_assert(get_subtract_flag(gb));
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(subn8, normal) {
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0xF2;

    subn8(gb, 1);

    cr_assert(gb->reg[a] == 0xF1);
    cr_assert(get_subtract_flag(gb));
    cr_assert_not(get_zero_flag(gb));
    cr_assert_not(get_half_flag(gb));
    cr_assert_not(get_carry_flag(gb));

    free_gameboy(gb);
}

Test(subn8, half_carry) {
    gameboy *gb = make_gameboy();

    gb->reg[a] = 0x1E;

    subn8(gb, 0xF);

    cr_assert(gb->reg[a] == 0xF, "Math is hard");
    cr_assert(get_subtract_flag(gb), "What the fuck");
    cr_assert_not(get_carry_flag(gb), "WTH");
    cr_assert(get_half_flag(gb));
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(subn8, zero) {
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0x1;

    subn8(gb, 0x1);

    cr_assert(gb->reg[a] == 0x0);
    cr_assert(get_subtract_flag(gb));
    cr_assert(get_zero_flag(gb));
    cr_assert_not(get_half_flag(gb));
    cr_assert_not(get_carry_flag(gb));

    free_gameboy(gb);
}

Test(subn8, carry) {
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0xF;

    subn8(gb, 0x10);

    cr_assert(gb->reg[a] == 0xFF);
    cr_assert(get_carry_flag(gb));
    cr_assert_not(get_half_flag(gb), "Maybe");
    cr_assert(get_subtract_flag(gb));
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(xorr8, normal) {
    gameboy *gb = make_gameboy();

    gb->reg[a] = 0xAA;
    gb->reg[b] = 0x55;

    xorr8(gb, b);

    cr_assert(gb->reg[a] == 0xFF);
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(xorr8, zero) {
    gameboy *gb = make_gameboy();

    gb->reg[a] = 0xAA;
    gb->reg[b] = 0xAA;

    xorr8(gb, b);

    cr_assert(gb->reg[a] == 0x0);
    cr_assert(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(xorhl, normal) {
    gameboy *gb = make_gameboy();

    gb->reg[a] = 0xAA;
    gb->memory[0x1234] = 0x55;

    set_value_hl(gb, 0x1234);

    xorhl(gb);

    cr_assert(gb->reg[a] == 0xFF);
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(xorhl, zero) {
    gameboy *gb = make_gameboy();

    gb->reg[a] = 0xAA;
    gb->memory[0x1234] = 0xAA;
    set_value_hl(gb, 0x1234);
    xorhl(gb);

    cr_assert(gb->reg[a] == 0x0);
    cr_assert(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(xorn8, normal) {
    gameboy *gb = make_gameboy();

    gb->reg[a] = 0xAA;

    xorn8(gb, 0x55);

    cr_assert(gb->reg[a] == 0xFF);
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(xorn8, zero) {
    gameboy *gb = make_gameboy();

    gb->reg[a] = 0xAA;
    xorn8(gb, 0xAA);

    cr_assert(gb->reg[a] == 0x0);
    cr_assert(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(addr16, normal)
{
    gameboy *gb = make_gameboy();
    set_value_hl(gb, 0x1111);
    set_value_de(gb, 0x1111);

    addr16(gb, de);

    cr_assert(0x2222 == get_value_hl(gb));
    cr_assert_not(get_zero_flag(gb));
    cr_assert_not(get_subtract_flag(gb));
    cr_assert_not(get_carry_flag(gb));
    cr_assert_not(get_half_flag(gb));

    free_gameboy(gb);
}

Test(addr16, zero)
{
    gameboy *gb = make_gameboy();
    set_value_hl(gb, 0x0);
    set_value_de(gb, 0x0);

    addr16(gb, de);

    cr_assert(0x0 == get_value_hl(gb));
    cr_assert(get_zero_flag(gb));
    cr_assert_not(get_subtract_flag(gb));
    cr_assert_not(get_carry_flag(gb));
    cr_assert_not(get_half_flag(gb));

    free_gameboy(gb);
}

Test(addr16, half_flag)
{
    gameboy *gb = make_gameboy();
    set_value_hl(gb, 0x1FFF);
    set_value_de(gb, 0x1);

    addr16(gb, de);

    cr_assert(0x2000 == get_value_hl(gb));
    cr_assert_not(get_zero_flag(gb));
    cr_assert_not(get_subtract_flag(gb));
    cr_assert_not(get_carry_flag(gb));
    cr_assert(get_half_flag(gb));

    free_gameboy(gb);
}

Test(addr16, carry)
{
    gameboy *gb = make_gameboy();
    set_value_hl(gb, 0xFFFF);
    set_value_de(gb, 0x2);

    addr16(gb, de);

    cr_assert(0x1 == get_value_hl(gb));
    cr_assert_not(get_zero_flag(gb));
    cr_assert_not(get_subtract_flag(gb));
    cr_assert(get_carry_flag(gb));
    cr_assert(get_half_flag(gb));

    free_gameboy(gb);
}

Test(decr16, normal)
{
    gameboy *gb = make_gameboy();
    set_value_de(gb, 0x1111);

    decr16(gb, de);

    cr_assert(get_value_de(gb) == 0x1110);

    free_gameboy(gb);
}

Test(decr16, zero)
{
    gameboy *gb = make_gameboy();
    set_value_de(gb, 0x0);

    decr16(gb, de);

    cr_assert(get_value_de(gb) == 0xFFFF);

    free_gameboy(gb);
}

Test(incr16, normal)
{
    gameboy *gb = make_gameboy();
    set_value_de(gb, 0x0);

    incr16(gb, de);

    cr_assert(get_value_de(gb) == 0x1);

    free_gameboy(gb);
}

Test(incr16, FFFF)
{
    gameboy *gb = make_gameboy();
    set_value_de(gb, 0xFFFF);

    incr16(gb, de);

    cr_assert(get_value_de(gb) == 0x0);

    free_gameboy(gb);
}

Test(bitr8, true)
{
    gameboy *gb = make_gameboy();

    gb->reg[b] = 0x1;

    bitr8(gb, b, 0);

    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(bitr8, false)
{
    gameboy *gb = make_gameboy();

    gb->reg[b] = 0x1;

    bitr8(gb, b, 5);

    cr_assert(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(bithl, true)
{
    gameboy *gb = make_gameboy();

    set_value_hl(gb, 0x4321);

    gb->memory[0x4321] = 0x1;

    bithl(gb, 0);

    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(bithl, false)
{
    gameboy *gb = make_gameboy();

    set_value_hl(gb, 0x4321);

    gb->memory[0x4321] = 0x1;

    bithl(gb, 7);

    cr_assert(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(resr8, test)
{
    gameboy *gb = make_gameboy();

    gb->reg[c] = 0xFF;

    resr8(gb, c, 7);

    cr_assert(gb->reg[c] == 0x7F);

    free_gameboy(gb);
}

Test(reshl, test)
{
    gameboy *gb = make_gameboy();

    set_value_hl(gb, 0x1111);

    gb->memory[0x1111] = 0xFF;

    reshl(gb, 7);

    cr_assert(gb->memory[get_value_hl(gb)] == 0x7F);

    free_gameboy(gb);
}

Test(setr8, test)
{
    gameboy *gb = make_gameboy();

    setr8(gb, d, 5);

    cr_assert(gb->reg[d] == 0x20);

    free_gameboy(gb);
}

Test(sethl, test)
{
    gameboy *gb = make_gameboy();

    set_value_hl(gb, 0x1111);

    gb->memory[0x1111] = 0x0;

    sethl(gb, 7);

    cr_assert(gb->memory[get_value_hl(gb)] == 0x80);

    free_gameboy(gb);
}

Test(swapr8, normal)
{
    gameboy *gb = make_gameboy();

    gb->reg[e] = 0x12;

    swapr8(gb, e);

    cr_assert(gb->reg[e] == 0x21);
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(swapr8, zero)
{
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0x0;

    swapr8(gb, a);

    cr_assert(gb->reg[a] == 0x0);
    cr_assert(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(swaphl, normal)
{
    gameboy *gb = make_gameboy();
    gb->memory[0x1234] = 0x24;
    set_value_hl(gb, 0x1234);

    swaphl(gb);

    cr_assert(gb->memory[0x1234] == 0x42);
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(swaphl, zero)
{
    gameboy *gb = make_gameboy();
    gb->memory[0x1234] = 0x0;
    set_value_hl(gb, 0x1234);

    swaphl(gb);
    cr_assert(gb->memory[0x1234] == 0x0);
    cr_assert(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(rlr8, normal)
{
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0x12;

    rlr8(gb,a);

    cr_assert(gb->reg[a] == 0x24);
    cr_assert_not(get_zero_flag(gb));
    cr_assert_not(get_carry_flag(gb));

    free_gameboy(gb);
}

Test(rlr8, carry)
{
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0xFF;

    rlr8(gb, a);

    cr_assert(gb->reg[a] == 0xFE);
    cr_assert(get_carry_flag(gb));
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(rlr8, zero)
{
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0x0;

    rlr8(gb,a);

    cr_assert(gb->reg[a] == 0x0);
    cr_assert(get_zero_flag(gb));
    cr_assert_not(get_carry_flag(gb));

    free_gameboy(gb);
}

Test(rlr8, with_carry)
{
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0x2;
    set_carry_flag(gb, true);

    rlr8(gb, a);

    cr_assert(gb->reg[a] == 0x5);
    cr_assert_not(get_zero_flag(gb));
    cr_assert_not(get_carry_flag(gb));

    free_gameboy(gb);
}

Test(rlhl, normal)
{
    gameboy *gb = make_gameboy();
    set_value_hl(gb, 0x1111);
    gb->memory[0x1111] = 0x12;

    rlhl(gb);

    cr_assert(gb->memory[0x1111] == 0x24, "%x", gb->memory[0x1111]);
    cr_assert_not(get_zero_flag(gb), "2");
    cr_assert_not(get_carry_flag(gb), "3");

    free_gameboy(gb);
}

Test(rlhl, carry)
{
    gameboy *gb = make_gameboy();
    set_value_hl(gb, 0x1111);
    gb->memory[0x1111] = 0xFF;

    rlhl(gb);

    cr_assert(gb->memory[0x1111] == 0xFE, "%x", gb->memory[0x1111]);
    cr_assert_not(get_zero_flag(gb), "2");
    cr_assert(get_carry_flag(gb), "3");

    free_gameboy(gb);
}

Test(rlhl, zero)
{
    gameboy *gb = make_gameboy();
    set_value_hl(gb, 0x1111);
    gb->memory[0x1111] = 0x00;

    rlhl(gb);

    cr_assert(gb->memory[0x1111] == 0x00, "%x", gb->memory[0x1111]);
    cr_assert(get_zero_flag(gb), "2");
    cr_assert_not(get_carry_flag(gb), "3");

    free_gameboy(gb);
}

Test(rlhl, with_carry)
{
    gameboy *gb = make_gameboy();
    set_value_hl(gb, 0x1111);
    gb->memory[0x1111] = 0x00;
    set_carry_flag(gb, true);

    rlhl(gb);

    cr_assert(gb->memory[0x1111] == 0x01, "%x", gb->memory[0x1111]);
    cr_assert_not(get_zero_flag(gb), "2");
    cr_assert_not(get_carry_flag(gb), "3");

    free_gameboy(gb);
}

Test(rla, normal)
{
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0x12;

    rla(gb);

    cr_assert(gb->reg[a] == 0x24);
    cr_assert_not(get_carry_flag(gb));

    free_gameboy(gb);
}

Test(rla, carry)
{
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0xFF;

    rla(gb);

    cr_assert(gb->reg[a] == 0xFE);
    cr_assert(get_carry_flag(gb));

    free_gameboy(gb);
}

Test(rla, zero)
{
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0x0;

    rla(gb);

    cr_assert(gb->reg[a] == 0x0);
    cr_assert_not(get_carry_flag(gb));

    free_gameboy(gb);
}

Test(rla, with_carry)
{
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0x2;
    set_carry_flag(gb, true);

    rla(gb);

    cr_assert(gb->reg[a] == 0x5);
    cr_assert_not(get_carry_flag(gb));

    free_gameboy(gb);
}

Test(rlcr8, normal)
{
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0x12;

    rlcr8(gb,a);

    cr_assert(gb->reg[a] == 0x24);
    cr_assert_not(get_zero_flag(gb));
    cr_assert_not(get_carry_flag(gb));

    free_gameboy(gb);
}

Test(rlcr8, carry)
{
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0xFF;

    rlcr8(gb, a);

    cr_assert(gb->reg[a] == 0xFF);
    cr_assert(get_carry_flag(gb));
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(rlcr8, zero)
{
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0x0;

    rlcr8(gb,a);

    cr_assert(gb->reg[a] == 0x0);
    cr_assert(get_zero_flag(gb));
    cr_assert_not(get_carry_flag(gb));

    free_gameboy(gb);
}

Test(rlchl, normal)
{
    gameboy *gb = make_gameboy();
    set_value_hl(gb, 0x1111);
    gb->memory[0x1111] = 0x12;

    rlchl(gb);

    cr_assert(gb->memory[0x1111] == 0x24, "%x", gb->memory[0x1111]);
    cr_assert_not(get_zero_flag(gb), "2");
    cr_assert_not(get_carry_flag(gb), "3");

    free_gameboy(gb);
}

Test(rlchl, carry)
{
    gameboy *gb = make_gameboy();
    set_value_hl(gb, 0x1111);
    gb->memory[0x1111] = 0xFF;

    rlchl(gb);

    cr_assert(gb->memory[0x1111] == 0xFF, "%x", gb->memory[0x1111]);
    cr_assert_not(get_zero_flag(gb), "2");
    cr_assert(get_carry_flag(gb), "3");

    free_gameboy(gb);
}

Test(rlchl, zero)
{
    gameboy *gb = make_gameboy();
    set_value_hl(gb, 0x1111);
    gb->memory[0x1111] = 0x00;

    rlchl(gb);

    cr_assert(gb->memory[0x1111] == 0x00, "%x", gb->memory[0x1111]);
    cr_assert(get_zero_flag(gb), "2");
    cr_assert_not(get_carry_flag(gb), "3");

    free_gameboy(gb);
}

Test(rlca, normal)
{
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0x12;

    rlca(gb);

    cr_assert(gb->reg[a] == 0x24);
    cr_assert_not(get_carry_flag(gb));

    free_gameboy(gb);
}

Test(rlca, carry)
{
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0xFF;

    rlca(gb);

    cr_assert(gb->reg[a] == 0xFF);
    cr_assert(get_carry_flag(gb));

    free_gameboy(gb);
}

Test(rlca, zero)
{
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0x0;

    rlca(gb);

    cr_assert(gb->reg[a] == 0x0);
    cr_assert_not(get_carry_flag(gb));

    free_gameboy(gb);
}

Test(rrr8, normal)
{
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0x12;

    rrr8(gb,a);

    cr_assert(gb->reg[a] == 0x9);
    cr_assert_not(get_zero_flag(gb));
    cr_assert_not(get_carry_flag(gb));

    free_gameboy(gb);
}

Test(rrr8, carry)
{
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0xFF;

    rrr8(gb, a);

    cr_assert(gb->reg[a] == 0x7F, "Actual value: 0x%x", gb->reg[a]);
    cr_assert(get_carry_flag(gb));
    cr_assert_not(get_zero_flag(gb));

    free_gameboy(gb);
}

Test(rrr8, zero)
{
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0x0;

    rrr8(gb,a);

    cr_assert(gb->reg[a] == 0x0);
    cr_assert(get_zero_flag(gb));
    cr_assert_not(get_carry_flag(gb));

    free_gameboy(gb);
}

Test(rrr8, with_carry)
{
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0x02;
    set_carry_flag(gb, true);

    rrr8(gb, a);

    cr_assert(gb->reg[a] == 0x81, "Actual value: 0x%x", gb->reg[a]);
    cr_assert_not(get_zero_flag(gb));
    cr_assert_not(get_carry_flag(gb));

    free_gameboy(gb);
}

Test(rrhl, normal)
{
    gameboy *gb = make_gameboy();
    set_value_hl(gb, 0x1111);
    gb->memory[0x1111] = 0x12;

    rrhl(gb);

    cr_assert(gb->memory[0x1111] == 0x9, "%x", gb->memory[0x1111]);
    cr_assert_not(get_zero_flag(gb), "2");
    cr_assert_not(get_carry_flag(gb), "3");

    free_gameboy(gb);
}

Test(rrhl, carry)
{
    gameboy *gb = make_gameboy();
    set_value_hl(gb, 0x1111);
    gb->memory[0x1111] = 0xFF;

    rrhl(gb);

    cr_assert(gb->memory[0x1111] == 0x7F, "%x", gb->memory[0x1111]);
    cr_assert_not(get_zero_flag(gb), "2");
    cr_assert(get_carry_flag(gb), "3");

    free_gameboy(gb);
}

Test(rrhl, zero)
{
    gameboy *gb = make_gameboy();
    set_value_hl(gb, 0x1111);
    gb->memory[0x1111] = 0x00;

    rrhl(gb);

    cr_assert(gb->memory[0x1111] == 0x00, "%x", gb->memory[0x1111]);
    cr_assert(get_zero_flag(gb), "2");
    cr_assert_not(get_carry_flag(gb), "3");

    free_gameboy(gb);
}

Test(rrhl, with_carry)
{
    gameboy *gb = make_gameboy();
    set_value_hl(gb, 0x1111);
    gb->memory[0x1111] = 0x00;
    set_carry_flag(gb, true);

    rrhl(gb);

    cr_assert(gb->memory[0x1111] == 0x80, "%x", gb->memory[0x1111]);
    cr_assert_not(get_zero_flag(gb), "2");
    cr_assert_not(get_carry_flag(gb), "3");

    free_gameboy(gb);
}

Test(rra, normal)
{
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0x12;

    rra(gb);

    cr_assert(gb->reg[a] == 0x9);
    cr_assert_not(get_carry_flag(gb));

    free_gameboy(gb);
}

Test(rra, carry)
{
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0xFF;

    rra(gb);

    cr_assert(gb->reg[a] == 0x7F);
    cr_assert(get_carry_flag(gb));

    free_gameboy(gb);
}

Test(rra, zero)
{
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0x0;

    rra(gb);

    cr_assert(gb->reg[a] == 0x0);
    cr_assert_not(get_carry_flag(gb));

    free_gameboy(gb);
}

Test(rra, with_carry)
{
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0x2;
    set_carry_flag(gb, true);

    rra(gb);

    cr_assert(gb->reg[a] == 0x81);
    cr_assert_not(get_carry_flag(gb));

    free_gameboy(gb);
}

Test(rrcr8, normal)
{
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0x12;

    rrcr8(gb,a);

    cr_assert(gb->reg[a] == 0x9);
    cr_assert_not(get_zero_flag(gb));
    cr_assert_not(get_carry_flag(gb));

    free_gameboy(gb);
}

Test(rrcr8, carry)
{
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0xFF;

    rrcr8(gb, a);

    cr_assert(gb->reg[a] == 0xFF, "1");
    cr_assert(get_carry_flag(gb), "2");
    cr_assert_not(get_zero_flag(gb), "3");

    free_gameboy(gb);
}

Test(rrcr8, zero)
{
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0x0;

    rrcr8(gb,a);

    cr_assert(gb->reg[a] == 0x0);
    cr_assert(get_zero_flag(gb));
    cr_assert_not(get_carry_flag(gb));

    free_gameboy(gb);
}

Test(rrchl, normal)
{
    gameboy *gb = make_gameboy();
    set_value_hl(gb, 0x1111);
    gb->memory[0x1111] = 0x12;

    rrchl(gb);

    cr_assert(gb->memory[0x1111] == 0x09, "%x", gb->memory[0x1111]);
    cr_assert_not(get_zero_flag(gb), "2");
    cr_assert_not(get_carry_flag(gb), "3");

    free_gameboy(gb);
}

Test(rrchl, carry)
{
    gameboy *gb = make_gameboy();
    set_value_hl(gb, 0x1111);
    gb->memory[0x1111] = 0xFF;

    rrchl(gb);

    cr_assert(gb->memory[0x1111] == 0xFF, "%x", gb->memory[0x1111]);
    cr_assert_not(get_zero_flag(gb), "2");
    cr_assert(get_carry_flag(gb), "3");

    free_gameboy(gb);
}

Test(rrchl, zero)
{
    gameboy *gb = make_gameboy();
    set_value_hl(gb, 0x1111);
    gb->memory[0x1111] = 0x00;

    rrchl(gb);

    cr_assert(gb->memory[0x1111] == 0x00, "%x", gb->memory[0x1111]);
    cr_assert(get_zero_flag(gb), "2");
    cr_assert_not(get_carry_flag(gb), "3");

    free_gameboy(gb);
}

Test(rrca, normal)
{
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0x12;

    rrca(gb);

    cr_assert(gb->reg[a] == 0x9);
    cr_assert_not(get_carry_flag(gb));

    free_gameboy(gb);
}

Test(rrca, carry)
{
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0xFF;

    rrca(gb);

    cr_assert(gb->reg[a] == 0xFF);
    cr_assert(get_carry_flag(gb));

    free_gameboy(gb);
}

Test(rrca, zero)
{
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0x0;

    rrca(gb);

    cr_assert(gb->reg[a] == 0x0);
    cr_assert_not(get_carry_flag(gb));

    free_gameboy(gb);
}

Test(slra8, normal)
{
    gameboy *gb = make_gameboy();
    gb->reg[a] = 0x1;
    slar8(gb, a);

    cr_assert(gb->reg[a] == 0x2);
    cr_assert_not(get_carry_flag(gb));

    free_gameboy(gb);
}