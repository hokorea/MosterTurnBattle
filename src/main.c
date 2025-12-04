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
    if (!load_report(&player)){
        game_start(&player);
        
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
        
        add_pokemon_to_party(&player, pikachu);
    }

    while (!game_loop(&player));

    return 0;
}