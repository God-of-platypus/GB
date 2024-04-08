#include "instruction/register_intruction.h"

void adcr8(gameboy *gb, reg r)
{
    if (r > l || r < a)
    {
        return;
    }
    uint8_t reg = gb->reg[r];
    uint8_t carry = get_carry_flag(gb);
    uint8_t rega = gb->reg[a];
    uint8_t res = rega + reg + carry;
    uint16_t cmp = rega + reg + carry;

    set_zero_flag(gb, res == 0);
    set_subtract_flag(gb, false);
    set_carry_flag(gb, cmp != res);
    set_half_flag(gb, (reg & 0xF) + carry > (0xF - (rega & 0xF)));
    gb->reg[a] = res;
}

void adchl(gameboy *gb)
{
    uint16_t pos = get_value_hl(gb);
    uint8_t value = gb->memory[pos];
    uint8_t rega = gb->reg[a];
    uint8_t carry = get_carry_flag(gb);
    uint16_t cmp = rega + carry + value;
    uint8_t res = rega + carry + value;

    set_zero_flag(gb, res == 0);
    set_subtract_flag(gb, false);
    set_carry_flag(gb, cmp != res);
    set_half_flag(gb, (rega & 0xF) + carry + (value & 0xF) > 0xF);

    gb->reg[a] = res;
}

void adcn8(gameboy *gb, uint8_t value)
{
    uint8_t rega = gb->reg[a];
    uint8_t carry = get_carry_flag(gb);
    uint16_t cmp = value + carry + rega;
    uint8_t res = value + carry + rega;

    set_zero_flag(gb, res == 0);
    set_subtract_flag(gb, false);
    set_carry_flag(gb, cmp != res);
    set_half_flag(gb, (rega & 0xF) + carry + (value & 0xF) > 0xF);

    gb->reg[a] = res;
}

void addr8(gameboy *gb, reg r)
{
    if (r > l || r < a)
    {
        return;
    }
    uint8_t reg = gb->reg[r];
    uint8_t rega = gb->reg[a];
    uint8_t res = rega + reg;
    uint16_t cmp = rega + reg;

    set_zero_flag(gb, res == 0);
    set_subtract_flag(gb, false);
    set_carry_flag(gb, cmp != res);
    set_half_flag(gb, (reg & 0xF) > (0xF - (rega & 0xF)));
    gb->reg[a] = res;
}

void addhl(gameboy *gb)
{
    uint16_t pos = get_value_hl(gb);
    uint8_t value = gb->memory[pos];
    uint8_t rega = gb->reg[a];

    uint16_t cmp = rega + value;
    uint8_t res = rega + value;

    set_zero_flag(gb, res == 0);
    set_subtract_flag(gb, false);
    set_carry_flag(gb, cmp != res);
    set_half_flag(gb, (rega & 0xF) + (value & 0xF) > 0xF);

    gb->reg[a] = res;
}

void addn8(gameboy *gb, uint8_t value)
{
    uint8_t rega = gb->reg[a];
    uint16_t cmp = value + rega;
    uint8_t res = value + rega;

    set_zero_flag(gb, res == 0);
    set_subtract_flag(gb, false);
    set_carry_flag(gb, cmp != res);
    set_half_flag(gb, (rega & 0xF) + (value & 0xF) > 0xF);

    gb->reg[a] = res;
}

void andr8(gameboy *gb, reg r)
{
    if (r > l || r < a)
    {
        return;
    }
    uint8_t reg = gb->reg[r];
    uint8_t rega = gb->reg[a];
    uint8_t res = rega & reg;

    set_zero_flag(gb, res == 0);
    set_half_flag(gb, true);
    set_carry_flag(gb, false);
    set_subtract_flag(gb, false);

    gb->reg[a] = res;
}

void andhl(gameboy *gb)
{
    uint16_t pos = get_value_hl(gb);
    uint8_t value = gb->memory[pos];
    uint8_t rega = gb->reg[a];

    uint8_t res = rega & value;

    set_zero_flag(gb, res == 0);
    set_half_flag(gb, true);
    set_carry_flag(gb, false);
    set_subtract_flag(gb, false);

    gb->reg[a] = res;
}

void andn8(gameboy *gb, uint8_t value)
{
    uint8_t res = gb->reg[a] & value;

    set_zero_flag(gb, res == 0);
    set_half_flag(gb, true);
    set_carry_flag(gb, false);
    set_subtract_flag(gb, false);

    gb->reg[a] = res;
}

void cpr8(gameboy *gb, reg r)
{
    uint8_t reg = gb->reg[r];
    uint8_t rega = gb->reg[a];

    set_zero_flag(gb, reg == rega);
    set_subtract_flag(gb, true);
    set_carry_flag(gb, reg > rega);
    set_half_flag(gb, (0xF & reg) > (rega & 0xF));
}

void cphl(gameboy *gb)
{
    uint8_t reg = gb->memory[get_value_hl(gb)];
    uint8_t rega = gb->reg[a];

    set_zero_flag(gb, reg == rega);
    set_subtract_flag(gb, true);
    set_carry_flag(gb, reg > rega);
    set_half_flag(gb, (0xF & reg) > (rega & 0xF));
}

void cpn8(gameboy *gb, uint8_t value)
{
    uint8_t rega = gb->reg[a];

    set_zero_flag(gb, rega == value);
    set_subtract_flag(gb, true);
    set_carry_flag(gb, value > rega);
    set_half_flag(gb, (0xF & value) > (rega & 0xF));
}

void decr8(gameboy *gb, reg r)
{
    if (r > l || r < a)
    {
        return;
    }

    uint8_t reg = gb->reg[r] - 1;
    bool half = (reg & 0xF) == 0xF;

    set_subtract_flag(gb, true);
    set_zero_flag(gb, reg == 0);
    set_half_flag(gb, half);

    gb->reg[r] = reg;
}

void dechl(gameboy *gb)
{
    uint8_t reg = gb->memory[get_value_hl(gb)] - 1;

    set_subtract_flag(gb, true);
    set_zero_flag(gb, reg == 0);
    set_half_flag(gb, (reg & 0xF) == 0xF);

    gb->memory[get_value_hl(gb)] = reg;
}

void incr8(gameboy *gb, reg r)
{
    if (r > l || r < a)
    {
        return;
    }
    uint8_t reg = gb->reg[r] + 1;

    set_carry_flag(gb, gb->reg[r] == 0xFF);
    set_zero_flag(gb, reg == 0);
    set_half_flag(gb, (reg & 0xF) == 0x0);

    gb->reg[r] = reg;    
}

void inchl(gameboy *gb) 
{
    uint8_t reg = gb->memory[get_value_hl(gb)] + 1;

    set_carry_flag(gb , gb->memory[get_value_hl(gb)] == 0xFF);
    set_zero_flag(gb, reg == 0);
    set_half_flag(gb, (reg & 0xF) == 0x0);

    gb->memory[get_value_hl(gb)] = reg;
}

void orr8(gameboy *gb, reg r){
    set_subtract_flag(gb, false);
    set_half_flag(gb, false);
    set_carry_flag(gb, false);
    set_zero_flag(gb, (gb->reg[r] & gb->reg[a]) == 0);

    gb->reg[a] &= gb->reg[r];
}

void orhl(gameboy *gb) 
{
    set_subtract_flag(gb, false);
    set_half_flag(gb, false);
    set_carry_flag(gb, false);
    gb->reg[a] &= gb->memory[get_value_hl(gb)];
    set_zero_flag(gb, gb->reg[a] == 0);

}

void orn8(gameboy *gb, uint8_t value) 
{
    set_subtract_flag(gb, false);
    set_half_flag(gb, false);
    set_carry_flag(gb, false);
    gb->reg[a] &= value;
    set_zero_flag(gb, gb->reg[a] == 0);
}

void sbcr8(gameboy *gb, reg r)
{
    if (r > l || r < a)
    {
        return;
    }
    uint8_t carry = get_carry_flag(gb);
    uint8_t reg = gb->reg[r];
    uint8_t rega = gb->reg[a];

    uint8_t res = rega - reg - carry;


    set_zero_flag(gb, res == 0);
    set_subtract_flag(gb, true);
    set_carry_flag(gb, reg + carry > rega);
    set_half_flag(gb, ((reg & 0xF) + carry) > (rega & 0xF));

    gb->reg[a] = res;
}

void sbchl(gameboy *gb) 
{
    uint8_t reg = gb->memory[get_value_hl(gb)];
    uint8_t rega = gb->reg[a];
    uint8_t carry = get_carry_flag(gb);

    uint8_t res = rega - reg - carry;


    set_zero_flag(gb, res == 0);
    set_subtract_flag(gb, true);
    set_carry_flag(gb, reg + carry > rega);
    set_half_flag(gb, ((reg & 0xF) + carry) > (rega & 0xF));

    gb->reg[a] = res;
}

void sbcn8(gameboy *gb, uint8_t value) 
{
    uint8_t reg = value;
    uint8_t rega = gb->reg[a];
    uint8_t carry = get_carry_flag(gb);

    uint8_t res = rega - reg - carry;


    set_zero_flag(gb, res == 0);
    set_subtract_flag(gb, true);
    set_carry_flag(gb, reg + carry > rega);
    set_half_flag(gb, ((reg & 0xF) + carry) > (rega & 0xF));

    gb->reg[a] = res;
}
