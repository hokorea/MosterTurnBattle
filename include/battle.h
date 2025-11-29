#ifndef BATTLE_H
#define BATTLE_H

#include "types.h"

#define MAX_MOVES 4

typedef struct Move{
    const char *name; // 기술 이름
    int power; // 위력
    MoveCategory category;
} Move;

typedef struct Pokemon{
    const char *name; // 포켓몬 이름

    int level; // 레벨
    int exp; // 현재 경험치

    int max_hp; // 최대 체력
    int hp; // 현재 체력

    int atk; // 공격
    int def; // 방어
    int sp_atk; // 특수공격
    int sp_def; // 특수방어
    int speed; // 속도

    Move moves[MAX_MOVES]; // 기술
    int move_count; // 기술 개수
} Pokemon;

// 데미지 계산 함수
int calc_damage(Pokemon *attacker, Pokemon *defender, Move *move);

// 포켓몬 상태 출력
void print_status(Pokemon *p);

// 한 턴 진행 (플레이어 <-> 적)
void battle_turn(Pokemon *player, Pokemon *enemy, Move *player_move, Move *enemy_move);

// 플레이어 기술 목록 출력
void print_moves(Pokemon *p);

// 플레이어가 사용할 기술 선택
Move* choose_player_move(Pokemon *p);

// 적이 사용할 기술 선택
Move* choose_enemy_move(Pokemon *p);

// 경험치 획득
void gain_exp(Pokemon *p, int amount);

// 레벨업 시 스탯 증가
void level_up_stats(Pokemon *p);

// 공격
void do_attack(Pokemon *attacker, Pokemon *defender, Move *move, ActorType attacker_type, ActorType defender_type);

#endif