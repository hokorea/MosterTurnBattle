#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "battle.h"

#define MAX_MOVES 4

// 데미지 계산 함수
int calc_damage(Pokemon *attacker, Pokemon *defender, Move *move){
    int attack_stat, defend_stat;

    if (move->category == MOVE_PHYSICAL){
        attack_stat = apply_stage(attacker->atk, attacker->atk_stage);
        defend_stat = apply_stage(defender->def, defender->def_stage);
    } else if (move->category == MOVE_SPECIAL) {
        attack_stat = apply_stage(attacker->sp_atk, attacker->sp_atk_stage);
        defend_stat = apply_stage(defender->sp_def, defender->sp_def_stage);
    } else {
        return 0;
    }

    if (defend_stat <= 0) defend_stat = 1; // 0 나누기 방지

    int level = attacker->level;

    // 1) 기본 데미지 계산 (정수 연산 주의)
    int base = (((2 * level / 5 + 2) * move->power * attack_stat) / defend_stat) / 50 + 2;
    
    // 2) 난수 보정 (85 ~ 100%)
    int rand_percent = (rand() % 16) + 85; // 85 ~ 100
    int damage = base * rand_percent / 100;

    // Damage ≈ [ ((2 × Level / 5 + 2) × Power × Atk / Def) / 50 + 2 ] × Random(0.85–1.00)

    if (damage < 1) damage = 1;

    return damage;
}

// 포켓몬 상태 출력
void print_status(Pokemon *p){
    printf("%s  HP: %d / %d\n", p->name, p->hp, p->max_hp);
}

// 한 턴 동안 선공, 후공으로 공격
void battle_turn(Pokemon *player, Pokemon *enemy, Move *player_move, Move *enemy_move){
    // 제대로 된 입력이 아닌 경우 return
    if (player_move == NULL) return;

    // 선공 후공 선택
    Pokemon *first, *second;
    Move *first_move, *second_move;
    ActorType first_type;
    ActorType second_type;

    if (player->speed > enemy->speed){
        first = player;
        first_move = player_move;
        second = enemy;
        second_move = enemy_move;
        first_type = ACTOR_PLAYER_MON;
        second_type = ACTOR_WILD_MON;
    } else if (player->speed < enemy->speed){
        first = enemy;
        first_move = enemy_move;
        second = player;
        second_move = player_move;
        first_type = ACTOR_WILD_MON;
        second_type = ACTOR_PLAYER_MON;
    } else{
        // 스피드가 같으면 랜덤으로 선공 결정
        if (rand() % 2 == 0){
            first = player;
            first_move = player_move;
            second = enemy;
            second_move = enemy_move;
            first_type = ACTOR_PLAYER_MON;
            second_type = ACTOR_WILD_MON;
        } else{
            first = enemy;
            first_move = enemy_move;
            second = player;
            second_move = player_move;
            first_type = ACTOR_WILD_MON;
            second_type = ACTOR_PLAYER_MON;
        }
    }

    // 선공 공격
    do_attack(first, second, first_move, first_type, second_type);

    // 첫 번째 공격에 맞고 쓰러졌으면 두 번째 행동 없음
    if (second->hp <= 0){
        return;
    }

    // 후공 반격
    do_attack(second, first, second_move, second_type, first_type);
    
}

// 기술 목록 출력
void print_moves(Pokemon *p){
    for (int i = 0; i < MAX_MOVES; i++){
        if (i >= p->move_count)
            printf("%d) -\n", i + 1);
        else
            printf("%d) %s\n", i + 1, p->moves[i].name);
    }
}

// 플레이어 기술 선택
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

// 적 기술 선택 (현재: 랜덤)
Move* choose_enemy_move(Pokemon *p){
    int choose_num = rand() % p->move_count;
    // 디버깅
    // printf("%d %d\n", p->move_count, choose_num);
    return &(p->moves[choose_num]);
}

// 경험치 획득
void gain_exp(Pokemon *p, int amount){
    p->exp += amount;

    // 레벨 * 10 이상이면 레벨업
    int needed = p->level * 10;
    while (p->exp >= needed){
        p->exp -= needed;
        p->level++;
        level_up_stats(p);
        needed = p->level * 10;
    }
}

// 레벨업 시 스탯 증가
void level_up_stats(Pokemon *p){
    p->max_hp += 3;
    p->atk += 2;
    p->def += 1;

    printf("\n%s의 레벨이 올랐다! Lv.%d\n", p->name, p->level);
}

void do_attack(Pokemon *attacker, Pokemon *defender, Move *move, ActorType attacker_type, ActorType defender_type){
    if (move == NULL) return;

    // 누가 치는지에 따라 문구 다르게
    switch (attacker_type){
    case ACTOR_PLAYER_MON:{
        printf("\n%s의 %s!\n", attacker->name, move->name);
        break;
    }
    case ACTOR_WILD_MON:{
        printf("\n야생 %s의 %s!\n", attacker->name, move->name);
        break;
    }
    case ACTOR_ENEMY_TRAINER_MON:{
        printf("\n상대 %s의 %s!\n", attacker->name, move->name);
        break;
    }
    }

    // 명중률 체크
    int roll = rand() % 100; // 0 ~ 99

    if (roll >= move->accuracy) {
        // 빗나감
        switch (attacker_type)
        {
        case ACTOR_PLAYER_MON:{
            printf("\n그러나 %s의 공격은 빗나갔다!\n", attacker->name);
            break;
        }
        case ACTOR_WILD_MON:{
            printf("\n그러나 야생 %s의 공격은 빗나갔다!\n", attacker->name);
            break;
        }
        case ACTOR_ENEMY_TRAINER_MON:{
            printf("\n그러나 상대 %s의 공격은 빗나갔다!\n", attacker->name);
            break;
        }
        }
        return; // 데미지 없이 턴 종료
    }

    if (move->category == MOVE_STATUS){
        apply_status_move(attacker, defender, move, attacker_type, defender_type);
        return;
    }

    // 급소 판정
    int is_crit = (rand() % 16 == 0);

    // 데미지 계산
    int damage = calc_damage(attacker, defender, move);

    // 급소 배율
    if (damage > 0 && is_crit) { 
        damage = damage * 3 / 2; 

        printf("\n급소에 맞았다!\n");
    }

    // HP 감소
    defender->hp -= damage;
    if (defender->hp < 0) defender->hp = 0;

    // 디버깅
    printf("%s에게 %d의 데미지!\n", defender->name, damage);

    // 공격을 받는 쪽이 쓰러졌는지 체크
    if (defender->hp <= 0) {
        switch (defender_type)
        {
        case ACTOR_WILD_MON:{
            printf("야생 %s는(은) 쓰러졌다!\n", defender->name);
            break;
        }
        case ACTOR_PLAYER_MON:{
            printf("%s는(은) 쓰러졌다!\n", defender->name);
            break;
        }
        case ACTOR_ENEMY_TRAINER_MON:{
            printf("상대 %s는(은) 쓰러졌다!\n", defender->name);
            break;
        }
        }
        return;
    }
}

int apply_stage(int stat, int stage){
    if (stage > 6) stage = 6;
    if (stage < -6) stage = -6;

    if (stage >= 0){
        return stat * (2 + stage) / 2;
    } else {
        return stat * 2 / (2 - stage);
    }
}

void apply_status_move(Pokemon *attacker, Pokemon *defender, Move *move, ActorType attacker_type, ActorType defender_type){
    if (strcmp(move->name, "울음소리") == 0){
        if (defender->atk_stage > -6){
            defender->atk_stage--;

            printf("%s의\n공격이 떨어졌다!\n", defender->name);
        } else{
            printf("%s의\n공격은 더 떨어지지 않는다!\n", defender->name);
        }
    }
}