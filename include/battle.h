#ifndef BATTLE_H
#define BATTLE_H

typedef struct Pokemon{
    const char *name; // 포켓몬 이름
    int max_hp; // 최대 체력
    int hp; // 현재 체력
    int atk; // 공격력
    int def; // 방어력
} Pokemon;

typedef struct Move{
    const char *name; // 기술 이름
    int power; // 위력
} Move;

// 데미지 계산 함수
int calc_damage(Pokemon *attacker, Pokemon *defender, Move *move);

// 포켓몬 상태 출력
void print_status(Pokemon *p);

// 한 턴 진행 (플레이어 -> 적 -> 반격)
void battle_turn(Pokemon *player, Pokemon *enemy, Move *player_move, Move *enemy_move);

#endif