#include <string.h>

#include "pokemon.h"

void init_status(Pokemon *p){
    p->atk_stage = 0;
    p->def_stage = 0;
    p->sp_atk_stage = 0;
    p->sp_def_stage = 0;
    p->speed_stage = 0;
    p->accuracy_stage = 0;
}

static int calc_hp(int base, int level) {
    return base + level * 3;
}

static int calc_stat(int base, int level) {
    return base + level * 2;
}

Pokemon create_pokemon_from_species(int dex_no, int level)
{
    Pokemon p = (Pokemon){0};

    const SpeciesData *s = get_species(dex_no);
    if (!s) return p;

    p.dex_no = dex_no;
    
    strncpy(p.name, s->name, sizeof(p.name));
    p.name[sizeof(p.name) - 1] = '\0';   // 널문자 보장

    p.level = level;

    p.max_hp = calc_hp(s->base_hp, level);
    p.hp = p.max_hp;

    p.atk = calc_stat(s->base_atk, level);
    p.def = calc_stat(s->base_def, level);
    p.sp_atk = calc_stat(s->base_sp_atk, level);
    p.sp_def = calc_stat(s->base_sp_def, level);
    p.speed = calc_stat(s->base_speed, level);

    return p;
}