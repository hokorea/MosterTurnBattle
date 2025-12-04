#include <stdio.h>
#include <string.h>

#include "game.h"
#include "battle.h"

// 초기화 시스템
void game_start(Trainer *player){
    char input_name[16];
    printf("\n...... ...... ......\n...... ...... ......\n");
    printf("\n으-음 음냐 음냐...\n...... ...... ......\n");
    printf("\n오잉? 이런 시간에\n손님이 왔는가...\n");
    printf("\n이야- 오래 기다리게 했구나!\n");
    printf("\n포켓몬스터의 세계에\n잘 왔다!\n");
    printf("\n내 이름은 오박사\n");
    printf("\n모두에게는 포켓몬 박사라고\n알려져 있단다\n");
    printf("\n그건 그렇고 너는\n모험이 처음인 게냐?\n");
    printf("\n우선 내가\n이 세계에 대한 것을 가르쳐주마!\n");

    printf("\n이 세계에는 포켓몬스터\n...줄여서 포켓몬이라\n불리는 생명체가\n도처에 살고 있다!\n");
    printf("\n우리 인간은\n포켓몬과 사이좋게 살고 있지\n");
    printf("\n함께 놀기도 하고\n힘을 합쳐 일하기도 하고\n");
    printf("\n그리고 포켓몬끼리 싸우게 하여\n유대감을 돈독히 다지기도 하고...\n");
    printf("\n나는 그런 포켓몬들을\n자세히 알기 위해\n");
    printf("\n매일 연구를\n계속하고 있는 것이란다!\n");

    // ========= 함수 구현 필요 ========
    printf("\n그건 그렇고... 이제 슬슬\n자네에 대해 알아보도록 하지!\n");
    printf("\n자네는 남자인가?\n아니면 여자인가?\n어느 쪽인가를 알려주게나\n");
    // 남자 여자 고르는 함수 추가
    // 자네는 %s로구나?(y/n)
    // n면 처음부터 시작

    printf("\n그럼 이름을 알려주게나!\n");
    printf("\n당신의 이름은? => ");
    scanf("%s", input_name);
    // n면 처음부터 시작
    printf("%s이로구나?(y/n)\n", input_name);
    // ================================
    printf("\n%s!!\n준비는 되었는가?\n", input_name);
    printf("\n드디어 이제부터\n너만의 이야기가 시작된다!\n");
    printf("\n즐거운 일도 괴로운 일도\n한가득 너를 기다리고 있겠지!\n");
    printf("\n꿈과 모험과!\n포켓몬스터의 세계로!\n레츠 고-!\n");
    printf("\n그럼 다음에 다시 만나자!\n");

    init_trainer(player, input_name, ACTOR_PLAYER);
}

// 게임 루프
int game_loop(Trainer *player){
    show_main_menu();
    Menu choose;
    do{
        choose = menu_select();
    }
    while (choose > 5); 
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
        if (battle_loop(player, &enemy) == BATTLE_LOSE){
            heal_pokemon(player);
        }
        return 0;
    }
    case MENU_PARTY:{
        print_party(player);
        return 0;
    }
    case MENU_CENTER:{
        open_pokemon_center(player);
        return 0;
    }
    case MENU_SHOP:{
        // open_friendly_shop(player);
        return 0;
    }
    case MENU_REPORT:{
        write_report(player);
        return 1;
    }
    default:
        break;
    }
    return 0;
}

Menu menu_select(void){
    int choose;
    scanf("%d", &choose);
    return choose - 1;
}

// 메뉴 시스템
void show_main_menu(void){
    printf("\n======================\n");
    printf("1) 포켓몬 배틀\n");
    printf("2) 포켓몬\n");
    printf("3) 포켓몬센터\n");
    printf("4) 프렌들리숍\n");
    printf("5) 저장하고 나가기\n");
    printf("======================\n");
}

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
        heal_pokemon(player);
        return;
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

void heal_pokemon(Trainer *player){
    printf("\n그럼\n맡아 드리겠습니다!\n\n");
    for (int i = 0; i < player->party_count; i++){
        Pokemon *p = &(player->party[i]);
        p->hp = p->max_hp;
        init_status(p);
        for (int j = 0; j < player->party[i].move_count; j++){
            Move *m = &(player->party[i].moves[j]);
            m->pp = m->max_pp;
        }
    }
    printf("오래 기다리셨습니다!\n\n");
    printf("맡겨 두신 포켓몬이\n모두 건강해졌습니다!\n\n");

    printf("또 언제든지\n이용해 주세요!\n\n");
    printf("======================\n");
}

/*
void open_friendly_shop(Trainer *player) {
    // 구매, 판매 메뉴
}
*/

// 세이브, 로드, 기타 확장 요소
void write_report(const Trainer *player){
    printf("======================\n");
    // n면 return
    printf("\n지금까지의 활약을\n포켓몬 리포트로 작성할까요?(y/n)");
    // n면 return
    printf("\n전에 작성한 리포트에\n덮어써도 괜찮습니까?(y/n)\n");

    printf("\n포켓몬 리포트를 작성하고 있습니다\n전원을 끄지 않도록 해주십시오\n");

    FILE *fp = fopen("save/report.txt", "w");   // 매번 새로 덮어쓰기
    if (!fp) {
        printf("리포트 파일을 열 수 없습니다: %s\n", "report.txt");
        return;
    }

    fprintf(fp, "NAME %s\n", player->name);                // 트레이너 이름
    fprintf(fp, "PARTY %d\n", player->party_count);        // 파티 수

    for (int i = 0; i < player->party_count; i++) {
        Pokemon p = player->party[i];

        fprintf(fp, "\nPOKEMON\n");
        fprintf(fp, "NAME %s\n", p.name);
        fprintf(fp, "LEVEL %d\n", p.level);
        fprintf(fp, "HP %d %d\n", p.hp, p.max_hp);
        fprintf(fp, "STATS %d %d %d %d %d\n",
                p.atk, p.def, p.sp_atk, p.sp_def, p.speed);
        fprintf(fp, "MOVES %d\n", p.move_count);

        for (int j = 0; j < p.move_count; j++) {
            Move m = p.moves[j];
            fprintf(fp, "MOVE %s %d %d %d %d\n",
                    m.name, m.power, m.accuracy, m.pp, m.max_pp);
        }
    }

    fclose(fp);


    printf("\n%s는(은)\n리포트를 꼼꼼히 기록했다!\n(%s)\n", player->name, "report.txt");
}

int load_report(Trainer *player) {
    FILE *fp = fopen("save/report.txt", "r");
    if (!fp){
        fp = fopen("save/report.txt", "w");
        if (!fp) return 0; // 제대로 생성됐는지 확인

        fprintf(fp, "NAME Player\n");
        fprintf(fp, "PARTY 0\n");

        fclose(fp);
        return 0;   // 기본 파일 만들었으니 새 게임 시작
    }

    char token[64];

    // NAME <이름>
    if (fscanf(fp, "%63s %15s", token, player->name) != 2 || strcmp(token, "NAME") != 0) {
        fclose(fp);
        return 0;   // 형식이 틀림 → 새 게임
    }

    // PARTY <숫자>
    if (fscanf(fp, "%63s %d", token, &player->party_count) != 2 || strcmp(token, "PARTY") != 0) {
        fclose(fp);
        return 0;
    }

    // 값 검증
    if (player->party_count < 0 || player->party_count > MAX_PARTY) {
        fclose(fp);
        return 0;
    }

    // 파티 읽기
    for (int i = 0; i < player->party_count; i++) {
        Pokemon *p = &player->party[i];

        if (fscanf(fp, "%63s", token) != 1 || strcmp(token, "POKEMON") != 0) {
            fclose(fp);
            return 0;
        }

        if (fscanf(fp, "%63s %31s", token, p->name) != 2 || strcmp(token, "NAME") != 0) {
            fclose(fp);
            return 0;
        }

        fscanf(fp, "%63s %d", token, &p->level);     // LEVEL
        fscanf(fp, "%63s %d %d", token, &p->hp, &p->max_hp); // HP
        
        fscanf(fp, "%63s %d %d %d %d %d", token,
               &p->atk, &p->def, &p->sp_atk, &p->sp_def, &p->speed); // STATS
        
        fscanf(fp, "%63s %d", token, &p->move_count); // MOVES
        if (p->move_count > MAX_MOVES) p->move_count = MAX_MOVES;

        for (int j = 0; j < p->move_count; j++) {
            Move *m = &p->moves[j];
            fscanf(fp, "%63s %31s %d %d %d %d",
                token, m->name, &m->power, &m->accuracy, &m->pp, &m->max_pp);
        }
    }

    fclose(fp);
    while (1){
        switch (load_print(player))
        {
        case 1:
            return 1; // 로드 성공
        case 2:{
            return 0;
        }
        default:{
            printf("잘못된 입력입니다...\n");
        }
        }
    }  
    
}

int load_print(Trainer *player){
    int choose;
    printf("======================\n");
    printf("1) 모험을 계속한다\n");
    printf("\t주인공       %s\n", player->name);
    printf("2) 새로운 모험을 시작한다\n");
    printf("======================\n");
    scanf("%d", &choose);
    return choose;
}