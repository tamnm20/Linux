.PHONY: clean
vpath %.c ./ $(SRC_DIR)
vpath %.o $(OBJ_DIR)

INC_DIR = ./inc
SRC_DIR := ./src
OBJ_DIR := ./obj
OUTPUT_DIR := ./bin
SRC_FILES := $(wildcard ./src/*.c)
OBJ_FILES := $(patsubst ./src/%.c, %.o, $(SRC_FILES))

run: $(OUTPUT_DIR)/main
	$(OUTPUT_DIR)/main
$(OUTPUT_DIR)/main: main.o $(OBJ_DIR)/$(OBJ_FILES)
	gcc -o $(OUTPUT_DIR)/main $(OBJ_DIR)/main.o $(OBJ_FILES)
# $(OBJ_DIR)/main.o: main.c
# 	gcc -o ./obj/main.o -c main.c -I./inc/
# gcc -o ./obj/add.o -c ./src/add.c -I./inc/
# gcc -o ./obj/sub.o -c ./src/sub.c -I./inc/
%.o: %.c
	gcc -I$(INC_DIR) -c $< -o $(OBJ_DIR)/$@
clean:
	rm -rf $(OUTPUT_DIR)/* $(OBJ_DIR)/*


# test: a b c
# 	echo $@
# 	echo $<
# 	echo $(var)
# 	echo $^
# a:

# b:

# c:

# some_file:
# 	touch some_file
# 	touch clean

# .PHONY: clean
# clean:
# 	rm -f some_file
# #	rm -f clean


print-%:
	@echo $($(subst print-,,$@))