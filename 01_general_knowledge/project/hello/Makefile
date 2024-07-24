.PHONY: clean

CUR_DIR := .
INC_DIR = ./inc
SRC_DIR = ./src
OBJ_DIR := ./obj
OUTPUT_DIR := ./bin
SRC_FILES := $(wildcard ./src/*.c)
OBJ_TEMP := $(patsubst ./src/%.c, %.o, $(SRC_FILES))
OBJ_FILES := $(foreach wrd,$(foo),$(wrd)!)

vpath %.o $(OBJ_DIR)
vpath %.c $(SRC_DIR)

run: $(OUTPUT_DIR)/main
	$(OUTPUT_DIR)/main
$(OUTPUT_DIR)/main: main.o $(OBJ_FILES)
	gcc -o $(OUTPUT_DIR)/main $(OBJ_TEMP) $(OBJ_DIR)/main.o
%.o: %.c
	gcc -I$(INC_DIR) -c $< -o $(OBJ_DIR)/$@

readSymbol:
	readelf -sW ./obj/main.o 
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