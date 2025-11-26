#include <stdio.h>
#include "battle.h"

// 데미지 계산 함수
int calc_damage(Pokemon *attacker, Pokemon *defender, Move *move){
    int damage = move->power + attacker->atk - defender->def;
    if (damage < 1) damage = 1;
    return damage;
}

// 포켓몬 상태 출력
void print_status(Pokemon *p){
    printf("%s  HP: %d / %d\n", p->name, p->hp, p->max_hp);
}

// 한 턴 동안 플레이어 → 적, 적 → 플레이어 순서로 공격
void battle_turn(Pokemon *player, Pokemon *enemy, Move *player_move, Move *enemy_move){
    // 플레이어 공격
    printf("\n%s의 %s!\n", player->name, player_move->name);
    int dmg_to_enemy = calc_damage(player, enemy, player_move);
    enemy->hp -= dmg_to_enemy;
    if (enemy->hp < 0) enemy->hp = 0;

    // 디버깅
    printf("%s에게 %d의 데미지!\n", enemy->name, dmg_to_enemy);

    // 적 쓰러졌는지 체크
    if (enemy->hp <= 0) {
        printf("%s는(은) 쓰러졌다!\n", enemy->name);
        return;
    }

    // 적의 반격
    printf("\n적의 %s의 %s!\n", enemy->name, enemy_move->name);
    int dmg_to_player = calc_damage(enemy, player, enemy_move);
    player->hp -= dmg_to_player;
    if (player->hp < 0) player->hp = 0;

    // 디버깅
    printf("%s에게 %d의 데미지!\n", player->name, dmg_to_player);

    if (player->hp <= 0) {
        printf("%s는(은) 쓰러졌다!\n", player->name);
    }
}