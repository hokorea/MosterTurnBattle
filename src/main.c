#include <stdio.h>
#include <windows.h>
#include "../include/battle.h"

int main(void){
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // 플레이어 포켓몬 설정
    Pokemon player = {
        "피카츄",
        50, 50, 10, 5
    };

    // 적 포켓몬 설정
    Pokemon enemy ={
        "불꽃숭이", 
        40, 40, 8, 3
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

        // 디버깅
        printf("\n--- 턴 종료 후 상태 ---\n");
        print_status(&player);
        print_status(&enemy);
        printf("----------------------\n");
    }

    // 최종 결과
    if (player.hp > 0) {
        printf("\n플레이어가 승리했다!\n");
    } else {
        printf("\n플레이어는 눈앞이 깜깜해졌다...\n");
    }
    return 0;
}