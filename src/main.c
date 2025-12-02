#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "../include/battle.h"
#include "../include/trainer.h"

int main(void){
    srand(time(NULL));
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    Trainer player;
    char input_name[16];
    
    printf("너의 이름은 무엇이니? => ");
    scanf("%s", input_name);
    init_trainer(&player, input_name);

    // 플레이어 포켓몬 설정
    Pokemon pikachu = {
        "피카츄",
        5, 45,
        35, 35,  
        55, 40, 50, 50, 90,
        0, 0, 0, 0, 0, 0,
        {
            {"전기쇼크", 40, MOVE_SPECIAL, 100},
            {"울음소리", 0, MOVE_STATUS, 100}
        },
        2
    };

    // 적 포켓몬 설정
    Pokemon enemy ={
        "구구", 
        3, 0,
        40, 40,    
        45, 40, 35, 35, 56,
        0, 0, 0, 0, 0, 0,
        {
            {"몸통박치기", 35, MOVE_PHYSICAL, 95},
            {"모래뿌리기", 0, MOVE_STATUS, 100}
        },
        2
    };

    add_pokemon_to_party(&player, pikachu);

    print_party(&player);

    printf("=== 배틀 시작! ===\n");
    print_status(&player.party[0]);
    print_status(&enemy);

    printf("앗! 야생 %s(이)가 튀어나왔다!\n", enemy.name);
    printf("가랏! %s!\n", player.party[0].name);

    print_moves(&player.party[0]);

    // 둘 중 하나가 쓰러질 때까지 반복
    while (player.party[0].hp > 0 && enemy.hp > 0) {

        battle_turn(&player.party[0], &enemy, choose_player_move(&player.party[0]), choose_enemy_move(&enemy));

        // 디버깅
        printf("\n--- 턴 종료 후 상태 ---\n");
        print_status(&player.party[0]);
        print_status(&enemy);
        printf("----------------------\n");
    }

    // 최종 결과
    if (player.party[0].hp > 0) {
        int gained_exp = 10;
        printf("\n%s는(은) %d 경험치를 얻었다!\n\n", player.party[0].name, gained_exp);
        gain_exp(&player.party[0], gained_exp);
    } else {
        printf("\n%s에게는\n싸울 수 있는 포켓몬이 없다!\n\n", player.name);
        printf("%s는(은) 당황해서\n%d원을 잃어버렸다!\n\n", player.name, 10);
        printf("... ... ... ...\n\n");
        printf("%s는(은)\n눈앞이 깜깜해졌다...\n\n", player.name);
        printf("지쳐서 기절해 버린\n포켓몬들을 데리고\n%s는(은) 급하게\n포켓몬센터로 돌아갔다\n", player.name);
    }

    return 0;
}