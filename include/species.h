#ifndef SPECIES_H
#define SPECIES_H

#include "types.h"   // 타입 enum 존재

#define MAX_SPECIES  200   // 일단 넉넉하게 (실제 쓸 개수는 나중에)

typedef struct {
    int dex_no;        // 도감 번호
    const char *name;  // 종 이름

    int base_hp;
    int base_atk;
    int base_def;
    int base_sp_atk;
    int base_sp_def;
    int base_speed;

    Type type1;
    Type type2;        // 없으면 TYPE_NONE
}SpeciesData;

// 1) 도감 데이터 초기화 (지금은 하드코딩, 나중엔 파일 로딩으로 교체)
void init_species_data(void);

// 2) 도감 번호로 종족 데이터 가져오기
const SpeciesData *get_species(int dex_no);

// 3) 파일에서 포켓몬 데이터 가져오기
static int load_species_from_file();

#endif