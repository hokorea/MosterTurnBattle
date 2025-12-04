#ifndef MOVE_H
#define MOVE_H

#define MAX_MOVES 4

typedef struct Move{
    char name[32]; // 기술 이름
    int power; // 위력
    MoveCategory category; // 물리/특수/변화
    int accuracy; // 명중률 (0 ~ 100)

    int max_pp; // 최대 pp(파워포인트 : 기술을 사용할 수 있는 횟수)
    int pp; // 현재 pp

    Type type; // 타입
} Move;

#endif