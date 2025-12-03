#include <stdio.h>

#include "game.h"
#include "battle.h"

// 초기화 시스템
void game_start(Trainer *player){
    char input_name[16];

    printf("너의 이름은 무엇이니? => ");
    scanf("%s", input_name);
    init_trainer(player, input_name, ACTOR_PLAYER);
}

// 게임 루프
void game_loop(Trainer *player){
    show_main_menu();
    Menu choose;
    do{
        choose = menu_select();
    }
    while (choose > 3); 
    switch (choose)
    {
    case MENU_BATTLE:
        
        break;
    
    default:
        break;
    }
}

Menu menu_select(void){
    int choose;
    scanf("%d", &choose);
    return choose - 1;
}

// 배틀 시작
// void start_wild_battle(Trainer *player, Pokemon *wild_mon);
// void start_trainer_battle(Trainer *player, Trainer *enemy);

// 메뉴 시스템
void show_main_menu(void){
    printf("1) 포켓몬 배틀\n");
    printf("2) 포켓몬센터\n");
    printf("3) 프렌들리숍\n");
    printf("4) 저장하고 나가기\n");
}
// void show_party_menu(const Trainer *player);

// 세이브, 로드, 기타 확장 요소
// void save_game(const Trainer *player);
// void load_game(Trainer *player);
