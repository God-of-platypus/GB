#include "gameboy/gameboy.h"

gameboy *make_gameboy(void)
{
    gameboy *gb = malloc(sizeof(gameboy));
    if (gb == NULL)
    {
        return NULL;
    }
    uint8_t *mem = calloc(MEMORY_SIZE, sizeof(uint8_t));
    if (mem == NULL)
    {
        free(gb);
        return NULL;
    }
    uint8_t *reg = calloc(REGISTER_NUMBER, sizeof(uint8_t));
    if (reg == NULL)
    {
        free(gb);
        free(mem);
        return NULL;
    }

    gb->reg = reg;
    gb->memory = mem;
    gb->pc = PROGRAM_COUNTER;
    gb->sp = STACK_POINTER_DEFAULT;

    return gb;
}

void free_gameboy(gameboy *gb) {
    free(gb->reg);
    free(gb->memory);
    free(gb);
}
