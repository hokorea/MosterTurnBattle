#ifndef TRAINER_H
#define TRAINER_H

#include "pokemon.h"   // Pokemon 구조체 필요
#include "types.h" // ActorType 구조체 필요

#define MAX_PARTY 6

typedef struct Trainer {
    char name[16];

    ActorType trainer_type;

    Pokemon party[MAX_PARTY];
    int party_count;
} Trainer;

// 초기화
void init_trainer(Trainer *t, const char *name, ActorType trainer_type);

// 파티에 포켓몬 추가
void add_pokemon_to_party(Trainer *t, Pokemon mon);

// 파티 출력
void print_party(const Trainer *t);

#endif