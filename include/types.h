#ifndef TYPES_H
#define TYPES_H

// 공격자의 타입
typedef enum ActorType{
    ACTOR_PLAYER_MON,
    ACTOR_WILD_MON,
    ACTOR_ENEMY_TRAINER_MON
}ActorType;

// 물리/특수/변화
typedef enum MoveCategory{
    MOVE_PHYSICAL, // 물리: atk vs def
    MOVE_SPECIAL, // 특수: sp_atk vs sp_def
    MOVE_STATUS // 변화기: 능력치 변화, 상태이상 등
}MoveCategory;

typedef enum Type{
    TYPE_NORMAL,
    TYPE_ELECTRIC,
    TYPE_FLYING,
    TYPE_GROUND,
    TYPE_NONE
}Type;

#endif