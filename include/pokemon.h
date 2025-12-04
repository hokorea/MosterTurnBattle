#ifndef POKEMON_H
#define POKEMON_H

#include "types.h"
#include "move.h"

typedef struct Pokemon{
    char name[32]; // 포켓몬 이름

    int level; // 레벨
    int exp; // 현재 경험치

    int max_hp; // 최대 체력
    int hp; // 현재 체력

    int atk; // 공격
    int def; // 방어
    int sp_atk; // 특수공격
    int sp_def; // 특수방어
    int speed; // 속도

    // 단계 필드 (-6 ~ +6)
    int atk_stage, def_stage, sp_atk_stage, sp_def_stage, 
    speed_stage, accuracy_stage;

    Type type[2]; // 타입

    Move moves[MAX_MOVES]; // 기술
    int move_count; // 기술 개수
} Pokemon;

void init_status(Pokemon *p);

#endif