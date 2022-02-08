SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

CC := gcc -I $(SRC_DIR)

OUT_EXE := $(BIN_DIR)/program

C_FILES := $(shell find $(SRC_DIR) -type f)
SRC_ALL_DIRS := $(shell find $(SRC_DIR) -type d)
OBJ_ALL_DIRS := $(patsubst $(SRC_DIR)%,$(OBJ_DIR)%,$(SRC_ALL_DIRS))

all: setup compile build run
	@

setup: 
	@rm -drf $(OBJ_DIR)/*
	@mkdir -p $(OBJ_DIR) $(BIN_DIR) $(OBJ_ALL_DIRS)

compile: $(C_FILES:.c=)
	@

%:
	@$(CC) -c $@.c -o $(patsubst $(SRC_DIR)%,$(OBJ_DIR)%,$@.o) 

build:
	@$(CC) $(shell find $(OBJ_DIR) -type f -name "*.o") -o $(OUT_EXE) -lm

run:
	@$(OUT_EXE)
