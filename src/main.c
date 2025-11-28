#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "../include/battle.h"

int main(void){
    srand(time(NULL));
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // 플레이어 포켓몬 설정
    Pokemon player = {
        "피카츄",
        35, 35, 55, 40,
        {
            {"전기쇼크", 40},
            {"울음소리", 0},
        },
        2
    };

    // 적 포켓몬 설정
    Pokemon enemy ={
        "구구", 
        40, 40, 45, 40,
        {
            {"몸통박치기", 35},
            {"모래뿌리기", 0}
        },
        2
    };

    printf("=== 배틀 시작! ===\n");
    print_status(&player);
    print_status(&enemy);

    printf("앗! 야생 %s(이)가 튀어나왔다!\n", enemy.name);
    printf("가랏! %s!\n", player.name);

    print_moves(&player);

    // 둘 중 하나가 쓰러질 때까지 반복
    while (player.hp > 0 && enemy.hp > 0) {

        battle_turn(&player, &enemy, choose_player_move(&player), choose_enemy_move(&enemy));

        // 디버깅
        printf("\n--- 턴 종료 후 상태 ---\n");
        print_status(&player);
        print_status(&enemy);
        printf("----------------------\n");
    }

    // 최종 결과
    if (player.hp > 0) {
        printf("\n%s는(은) %d 경험치를 얻었다!\n\n", player.name, 10);
    } else {
        printf("\n%s에게는\n싸울 수 있는 포켓몬이 없다!\n\n", player.name);
        printf("%s는(은) 당황해서\n%d원을 잃어버렸다!\n\n", player.name, 10);
        printf("... ... ... ...\n\n");
        printf("%s는(은)\n눈앞이 깜깜해졌다...\n\n", player.name);
        printf("지쳐서 기절해 버린\n포켓몬들을 데리고\n%s는(은) 급하게\n포켓몬센터로 돌아갔다\n", player.name);
    }

    return 0;
}