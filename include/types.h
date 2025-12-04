#ifndef TYPES_H
#define TYPES_H

// 공격자의 타입
typedef enum ActorType{
    ACTOR_PLAYER,
    ACTOR_WILD,
    ACTOR_ENEMY_TRAINER
}ActorType;

// 물리/특수/변화
typedef enum MoveCategory{
    MOVE_PHYSICAL, // 물리: atk vs def
    MOVE_SPECIAL, // 특수: sp_atk vs sp_def
    MOVE_STATUS // 변화기: 능력치 변화, 상태이상 등
}MoveCategory;

typedef enum Type{
    TYPE_NORMAL = 1, // 노말
    TYPE_FIGHTING,   // 격투
    TYPE_FLYING,     // 비행
    TYPE_POISON,     // 독
    TYPE_GROUND,     // 땅
    TYPE_ROCK,       // 바위
    TYPE_BUG,        // 벌레
    TYPE_GHOST,      // 고스트
    TYPE_STEEL,      // 강철
    TYPE_FIRE,       // 불꽃
    TYPE_WATER,      // 물
    TYPE_GRASS,      // 풀
    TYPE_ELECTRIC,   // 전기
    TYPE_PSYCHIC,    // 에스퍼
    TYPE_ICE,        // 얼음
    TYPE_DRAGON,     // 드래곤
    TYPE_DARK,       // 악
    TYPE_FAIRY,      // 페어리

    TYPE_NONE        // 무타입 또는 에러 처리용
}Type;

typedef enum Menu{
    MENU_BATTLE,
    MENU_PARTY,
    MENU_CENTER,
    MENU_SHOP,
    MENU_REPORT
}Menu;

typedef enum BattleStatus{
    BATTLE_WIN,
    BATTLE_LOSE,
}BattleStatus;

#endif