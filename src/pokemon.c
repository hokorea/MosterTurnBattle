#include "pokemon.h"

void init_status(Pokemon *p){
    p->atk_stage = 0;
    p->def_stage = 0;
    p->sp_atk_stage = 0;
    p->sp_def_stage = 0;
    p->speed_stage = 0;
    p->accuracy_stage = 0;
}