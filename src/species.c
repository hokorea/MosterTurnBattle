#include <stdio.h>
#include <string.h>

#include "species.h"

static SpeciesData g_species[MAX_SPECIES + 1]; // 0번은 비워둠

static Type parse_type(const char *str)
{
    if (strcmp(str, "GRASS") == 0)  return TYPE_GRASS;
    if (strcmp(str, "FIRE") == 0)   return TYPE_FIRE;
    if (strcmp(str, "WATER") == 0)  return TYPE_WATER;
    if (strcmp(str, "POISON") == 0) return TYPE_POISON;
    if (strcmp(str, "NONE") == 0)   return TYPE_NONE;

    // 혹시 모르는 문자열이면 일단 NONE 처리
    return TYPE_NONE;
}

// 1) 도감 데이터 초기화 
void init_species_data(void){
    // 지금은 그냥 직접 채우기 (테스트용 몇 마리만)
    for (int i = 0; i <= MAX_SPECIES; i++) {
        g_species[i].dex_no = 0;   // 빈 슬롯 표시
    }

    g_species[1] = (SpeciesData){
        .dex_no = 1,
        .name = "Leafmon",
        .base_hp = 45,
        .base_atk = 49,
        .base_def = 49,
        .base_sp_atk = 65,
        .base_sp_def = 65,
        .base_speed = 45,
        .type1 = TYPE_GRASS,
        .type2 = TYPE_POISON
    };

    g_species[2] = (SpeciesData){
        .dex_no = 2,
        .name = "Flamemon",
        .base_hp = 39,
        .base_atk = 52,
        .base_def = 43,
        .base_sp_atk = 60,
        .base_sp_def = 50,
        .base_speed = 65,
        .type1 = TYPE_FIRE,
        .type2 = TYPE_NONE
    };

    // 나중에 여기 부분을 파일 읽기로 바꾸면 됨!
    // ex) load_species_from_file("data/pokemon_data.txt");
}

// 2) 도감 번호로 종족 데이터 가져오기
const SpeciesData *get_species(int dex_no){
    if (dex_no <= 0 || dex_no > MAX_SPECIES) {
        return NULL;
    }
    if (g_species[dex_no].dex_no == 0) {
        return NULL; // 빈 슬롯
    }
    return &g_species[dex_no];
}

// 3) 파일에서 포켓몬 데이터 가져오기
static int load_species_from_file(void){
    FILE *fp = fopen("data/pokemon_data.txt", "r");
    if (!fp) {
        perror("pokemon_data.txt 열기 실패");
        return 0;
    }

    char line[256];
    int line_num = 0;

    while (fgets(line, sizeof(line), fp)) {
        line_num++;
        printf("[DEBUG] line %d: %s", line_num, line);
    }

    fclose(fp);
    return line_num;
}