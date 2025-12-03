#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "../include/game.h"
#include "../include/battle.h"
#include "../include/trainer.h"
#include "../include/types.h"

int main(void){
    printf("[DEBUG BUILD] %s %s\n", __DATE__, __TIME__);

    srand(time(NULL));
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    Trainer player;
    game_start(&player);
    Trainer enemy = {
        "야생",
        ACTOR_WILD,
        {},
        0
    };

    // 플레이어 포켓몬 설정
    Pokemon pikachu = {
        "피카츄",
        5, 45,
        35, 35,  
        55, 40, 50, 50, 90,
        0, 0, 0, 0, 0, 0,
        {TYPE_ELECTRIC, TYPE_NONE},
        {
            {"전기쇼크", 40, MOVE_SPECIAL, 100, 30, 30, TYPE_ELECTRIC},
            {"울음소리", 0, MOVE_STATUS, 100, 40, 40, TYPE_NORMAL}
        },
        2
    };

    // 적 포켓몬 설정
    Pokemon pidgey ={
        "구구", 
        3, 0,
        40, 40,    
        45, 40, 35, 35, 56,
        0, 0, 0, 0, 0, 0,
        {TYPE_NORMAL, TYPE_FLYING},
        {
            {"몸통박치기", 35, MOVE_PHYSICAL, 95, 35, 35, TYPE_NORMAL},
            {"모래뿌리기", 0, MOVE_STATUS, 100, 15, 15, TYPE_GROUND}
        },
        2
    };
    
    add_pokemon_to_party(&player, pikachu);
    add_pokemon_to_party(&enemy, pidgey);

    battle_loop(&player, &enemy);

    return 0;
}