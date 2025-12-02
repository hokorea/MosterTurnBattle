#include <stdio.h>

#include "game.h"

// 초기화 시스템
void game_start(Trainer *player){
    char input_name[16];

    printf("너의 이름은 무엇이니? => ");
    scanf("%s", input_name);
    init_trainer(player, input_name);
}

// 게임 루프
void game_loop(Trainer *player);

// 배틀 시작
void start_wild_battle(Trainer *player, Pokemon *wild_mon);
void start_trainer_battle(Trainer *player, Trainer *enemy);

// 메뉴 시스템
void show_main_menu(void);
void show_party_menu(const Trainer *player);

// 세이브, 로드, 기타 확장 요소
void save_game(const Trainer *player);
void load_gmae(Trainer *player);
