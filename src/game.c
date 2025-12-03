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
    case MENU_BATTLE:{
        // 테스트용 구조체 선언
        Trainer enemy = {
            "야생",
            ACTOR_WILD,
            {},
            0
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
        add_pokemon_to_party(&enemy, pidgey);
        battle_loop(player, &enemy);
        break;
    }
    case MENU_CENTER:{
        open_pokemon_center(player);
        break;
    }
    default:
        break;
    }
}

Menu menu_select(void){
    int choose;
    scanf("%d", &choose);
    return choose - 1;
}

// 메뉴 시스템
void show_main_menu(void){
    printf("1) 포켓몬 배틀\n");
    printf("2) 포켓몬센터\n");
    printf("3) 프렌들리숍\n");
    printf("4) 저장하고 나가기\n");
}
// void show_party_menu(const Trainer *player);

// 게임 시스템
void open_pokemon_center(Trainer *player) {
    printf("======================\n");
    printf("안녕하세요!\n포켓몬센터입니다\n\n");
    printf("여기에서는 포켓몬의\nHP를 회복시켜 드립니다\n\n");
    printf("당신의 포켓몬을\n쉬게 하겠습니까?(y/n)\n");
    char choose;
    scanf(" %c", &choose);
    switch (choose)
    {
    case 'y': case 'Y':{
        printf("그럼\n맡아 드리겠습니다!\n\n");
        for (int i = 0; i < player->party_count; i++){
            player->party[i].hp = player->party[i].max_hp;
            for (int j = 0; j < player->party[i].move_count; j++){
                player->party[i].moves[j].pp = player->party[i].moves[j].max_pp;
            }
        }
        printf("오래 기다리셨습니다!\n\n");
        printf("맡겨 두신 포켓몬이\n모두 건강해졌습니다!\n\n");
        
        break;
    }
    case 'n': case 'N':
        break;
    default:
        printf("잘못된 값을 입력했습니다...\n");
        break;
    }
    printf("또 언제든지\n이용해 주세요!\n\n");
    printf("======================\n");
}

/*
void open_friendly_shop(Trainer *player) {
    // 구매, 판매 메뉴
}
*/

// 세이브, 로드, 기타 확장 요소
// void save_game(const Trainer *player);
// void load_game(Trainer *player);
