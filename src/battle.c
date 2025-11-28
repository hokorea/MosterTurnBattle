#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
    printf("%s", enemy_move->name); // 디버깅
    // 플레이어 공격
    printf("\n%s의 %s!\n", player->name, player_move->name);
    int dmg_to_enemy = calc_damage(player, enemy, player_move);
    enemy->hp -= dmg_to_enemy;
    if (enemy->hp < 0) enemy->hp = 0;

    // 디버깅
    printf("%s에게 %d의 데미지!\n", enemy->name, dmg_to_enemy);

    // 적 쓰러졌는지 체크
    if (enemy->hp <= 0) {
        printf("야생 %s는(은) 쓰러졌다!\n", enemy->name);
        return;
    }

    // 적의 반격
    printf("\n야생 %s의 %s!\n", enemy->name, enemy_move->name);
    int dmg_to_player = calc_damage(enemy, player, enemy_move);
    player->hp -= dmg_to_player;
    if (player->hp < 0) player->hp = 0;

    // 디버깅
    printf("%s에게 %d의 데미지!\n", player->name, dmg_to_player);

    if (player->hp <= 0) {
        printf("%s는(은) 쓰러졌다!\n", player->name);
    }
}

// 기술 목록 출력
void print_moves(Pokemon *p){
    for (int i = 0; i < 4; i++){
        if (i >= p->move_count)
            printf("%d) -\n", i + 1);
        else
            printf("%d) %s\n", i + 1, p->moves[i].name);
    }
}

Move* choose_player_move(Pokemon *p){
    int choose_num;

    printf("사용할 기술을 선택하세요: ");
    scanf("%d", &choose_num);
    if (choose_num <= p->move_count && choose_num > 0){
        return &(p->moves[choose_num - 1]);
    } else {
        printf("잘못된 입력입니다...\n");
        return NULL;
    }
}

Move* choose_enemy_move(Pokemon *p){
    int choose_num = rand() % p->move_count;
    printf("%d %d\n", p->move_count, choose_num);
    return &(p->moves[choose_num]);
}