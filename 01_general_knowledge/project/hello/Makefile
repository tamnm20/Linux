.PHONY: clean
CC := gcc
CUR_DIR := .
INC_DIR = ./inc
SRC_DIR = ./src
OBJ_DIR := ./obj
OUTPUT_DIR := ./bin
SRC_FILES := $(wildcard ./src/*.c)
OBJ_TEMP := $(patsubst ./src/%.c, %.o, $(SRC_FILES))
OBJ_FILES := $(foreach wrd,$(OBJ_TEMP),./obj/$(wrd))

vpath %.o $(OBJ_DIR)
vpath %.c $(SRC_DIR)

run: $(OUTPUT_DIR)/main
	$(OUTPUT_DIR)/main
$(OUTPUT_DIR)/main: main.o $(OBJ_TEMP)
	$(CC) -o $(OUTPUT_DIR)/main $(OBJ_FILES) $(OBJ_DIR)/main.o
%.o: %.c
	$(CC) -I$(INC_DIR) -c $< -o $(OBJ_DIR)/$@

readSymbol:
	readelf -sW ./obj/main.o 
clean:
	rm -rf $(OUTPUT_DIR)/* $(OBJ_DIR)/*

print-%:
	@echo $($(subst print-,,$@))