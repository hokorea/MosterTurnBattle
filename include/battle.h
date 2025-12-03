#ifndef BATTLE_H
#define BATTLE_H

#include "types.h"
#include "trainer.h"
#include "pokemon.h"
#include "move.h"

// 배틀을 실행시킬 함수
BattleStatus battle_loop(Trainer *player, Trainer *enemy);

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
void do_attack(Pokemon *attacker, Pokemon *defender, Move *move, 
    ActorType attacker_type, ActorType defender_type);

// 단계
int apply_stage(int stat, int stage);

// 변화 기술 처리
void apply_status_move(Pokemon *defender, Move *move, ActorType defender_type);

// 타입 상성
float get_type_effectiveness(Type move_type, Type target_type);

#endif