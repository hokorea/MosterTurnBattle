#include <stdio.h>
#include <string.h>

#include "trainer.h"

// 초기화
void init_trainer(Trainer *t, const char *name, ActorType trainer_type){
    // 이름 복사
    strncpy(t->name, name, sizeof(t->name));
    t->name[sizeof(t->name) - 1] = '\0'; // 안전 처리

    // 돈 초기값 설정
    t->trainer_type = trainer_type;

    // 파티 초기화
    t->party_count = 0;
}

// 파티에 포켓몬 추가
void add_pokemon_to_party(Trainer *t, Pokemon mon){
    if (t->party_count >= MAX_PARTY){
        printf("파티에 포켓몬이 가득찼습니다!\n");
        return;
    }

    t->party[t->party_count] = mon; // 구조체 통째로 복사
    t->party_count++;
}

// 파티 출력
void print_party(const Trainer *t){
    printf("\n=== %s의 포켓몬 ===\n", t->name);

    for (int i = 0; i < MAX_PARTY; i++){
        if (i < t->party_count)
            printf("%d) %s (Lv.%d) HP: %d/%d\n", i + 1, 
                t->party[i].name, t->party[i].level,
                t->party[i].hp, t->party[i].max_hp);
        else
            printf("%d) -\n", i + 1);
    }
    printf("========================\n");
}