# ============================
# MonsterTurnBattle Makefile
# (Windows CMD / PowerShell 호환 버전)
# ============================

# 컴파일러
CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -Iinclude

# 디렉토리
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = app

# 실행 파일 이름 (Windows는 .exe 자동 생성됨)
TARGET  = $(BIN_DIR)/monsterturnbattle.exe

# src/*.c → 자동 탐색
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# 기본 타겟
all: $(TARGET)

# 링크 단계
$(TARGET): $(OBJS)
	if not exist $(BIN_DIR) mkdir $(BIN_DIR)
	$(CC) $(OBJS) -o $@

# 컴파일 단계
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# 편의 명령어
.PHONY: clean run

run: $(TARGET)
	$(TARGET)

clean:
	del /Q $(OBJ_DIR)\*.o 2>nul || echo No object files
	del /Q $(TARGET) 2>nul || echo No exe file
