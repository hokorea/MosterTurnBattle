#include <stdio.h>
#include <windows.h>

typedef struct Pokemon{
    const char *name;
    int max_hp;
    int hp;
    int atk;
    int def;
} Pokemon;

typedef struct Move{
    const char *name;
    int power;
} Move;

int calc_damage(Pokemon *attacker, Pokemon *defender, Move *move);

void print_status(Pokemon *p);

void battle_turn(Pokemon *player, Pokemon *enemy, Move *player_move, Move *enemy_move);

int main(void){
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // 플레이어 포켓몬 설정
    Pokemon player = {
        "피카츄", // 이름
        50,       // max_hp
        50,       // hp
        10,       // atk
        5         // def
    };

    // 적 포켓몬 설정
    Pokemon enemy ={
        "불꽃숭이",
        40,
        40,
        8,
        3
    };

    // 둘이 쓸 기술 (일단 하나씩만)
    Move player_move = {"몸통박치기", 10};
    Move enemy_move  = {"할퀴기", 8};

    printf("=== 배틀 시작! ===\n");
    print_status(&player);
    print_status(&enemy);

    // 둘 중 하나가 쓰러질 때까지 반복
    while (player.hp > 0 && enemy.hp > 0) {
        battle_turn(&player, &enemy, &player_move, &enemy_move);

        printf("\n--- 턴 종료 후 상태 ---\n");
        print_status(&player);
        print_status(&enemy);
        printf("----------------------\n");
    }

    // 최종 결과
    if (player.hp > 0 && enemy.hp <= 0) {
        printf("\n플레이어가 승리했다!\n");
    } else if (enemy.hp > 0 && player.hp <= 0) {
        printf("\n플레이어는 눈앞이 깜깜해졌다...\n");
    } else {
        printf("\n둘 다 쓰러졌다!? (무승부)\n");
    }

    return 0;
}

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