#ifndef GAME_H
#define GAME_H

#include "trainer.h"
#include "battle.h"
#include "types.h"

// 초기화 시스템
void game_start(Trainer *player);
int info_set(Trainer *player);

// 게임 루프
int game_loop(Trainer *player);

// 메뉴 선택
Menu menu_select(void);

// 메뉴 시스템
void show_main_menu(void);

// 게임 시스템
void open_pokemon_center(Trainer *player);
void heal_pokemon(Trainer *player);
void open_friendly_shop(Trainer *player);

// // 세이브, 로드, 기타 확장 요소
int write_report(const Trainer *player);
int load_report(Trainer *player);
int load_print(Trainer *player);
int ask_yes_no(void);

#endif