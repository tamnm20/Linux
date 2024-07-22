
# INC_DIR := ./inc
# SRC_DIR := ./src
# OBJ_DIR := ./obj
# OUTPUT_DIR := ./bin
# SRC_FILES := $(wildcard ./src/*.c)
# OBJ_FILES := $(patsubst ./src/%.c, ./obj/%.o, $(SRC_FILES))

# run: main
# 	$(OUTPUT_DIR)/main
# main: main.o $(OBJ_FILES)
# 	gcc -o $(OUTPUT_DIR)/main $(OBJ_DIR)/main.o $(OBJ_FILES)
# 	tree
# main.o:
# 	gcc -o ./obj/main.o -c main.c -I./inc/
# # gcc -o ./obj/add.o -c ./src/add.c -I./inc/
# # gcc -o ./obj/sub.o -c ./src/sub.c -I./inc/
# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
# 	gcc -I$(INC_DIR) -c $< -o $@ 
# clean:
# 	rm -rf $(OUTPUT_DIR)/* $(OBJ_DIR)/*
# 	tree


# Recursive variable. This will print "later" below
one = one ${later_variable}
# Simply expanded variable. This will not print "later" below
two := two ${later_variable}

later_variable = later

all: 
	@echo $(one)
	@echo $(two)


print-%:
	@echo $($(subst print-,,$@))