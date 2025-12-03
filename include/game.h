#ifndef GAME_H
#define GAME_H

#include "trainer.h"
#include "battle.h"
#include "types.h"

// 초기화 시스템
void game_start(Trainer *player);

// 게임 루프
void game_loop(Trainer *player);

Menu menu_select(void);

// // 배틀 시작
// void start_wild_battle(Trainer *player, Pokemon *wild_mon);
// void start_trainer_battle(Trainer *player, Trainer *enemy);

// 메뉴 시스템
void show_main_menu(void);
// void show_party_menu(const Trainer *player);

// 게임 시스템
void open_pokemon_center(Trainer *player);
void open_friendly_shop(Trainer *player);

// // 세이브, 로드, 기타 확장 요소
// void save_game(const Trainer *player);
// void load_game(Trainer *player);

#endif