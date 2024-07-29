.PHONY: clean
CC := gcc
CUR_DIR := .
INC_DIR = $(CUR_DIR)/inc
SRC_DIR = $(CUR_DIR)/src
OBJ_DIR := $(CUR_DIR)/obj
LIB_DIR := $(CUR_DIR)/lib
LIB_STA_DIR := $(LIB_DIR)/static
OUTPUT_DIR := $(CUR_DIR)/bin
BIN_DIR := $(OUTPUT_DIR)
SRC_FILES := $(wildcard ./src/*.c)
OBJ_TEMP := $(patsubst ./src/%.c, %.o, $(SRC_FILES))
OBJ_FILES := $(foreach wrd,$(OBJ_TEMP),./obj/$(wrd))

vpath %.o $(OBJ_DIR)
vpath %.c $(SRC_DIR)

build_app_static: $(BIN_DIR)/hello_static
build_static_lib: $(LIB_STA_DIR)/libhello_static.a
link_static_lib: $(BIN_DIR)/hello_static_stalib

run_app_1: $(BIN_DIR)/hello_static_stalib
	@if test -f "./bin/hello_static" ; then \
		./bin/hello_static; \
	fi
	@if test -f "./bin/hello_static_stalib" ; then \
		./bin/hello_static_stalib; \
	fi

$(BIN_DIR)/hello_static: main.o $(OBJ_FILES)
	$(CC) -o $@ $^ -I./inc

run: $(OUTPUT_DIR)/main
	$(OUTPUT_DIR)/main
$(OUTPUT_DIR)/main: main.o $(OBJ_TEMP)
	$(CC) -o $(OUTPUT_DIR)/main $(OBJ_FILES) $(OBJ_DIR)/main.o
%.o: %.c
	$(CC) -I$(INC_DIR) -c $< -o $(OBJ_DIR)/$@

# Create the static library
$(LIB_STA_DIR)/libhello_static.a: hello_static.o
	ar rcs $@ $(OBJ_DIR)/hello_static.o

# Link statically
$(BIN_DIR)/hello_static_stalib: main.o $(OBJ_TEMP)
	$(CC) $(OBJ_DIR)/main.o $(OBJ_FILES) -L$(LIB_STA_DIR) -lhello_static -o $@

# Link dynamically with the shared library
$(BIN_DIR)/hello_shared_shalib: $(LIB_SHA_DIR)/libhello_shared.so
	$(CC) $(OBJ_DIR)/main.o $(OBJ_FILES) -L$(LIB_SHA_DIR) -lhello_shared -o $@


readSymbol:
	readelf -sW ./obj/main.o 
clean:
	rm -rf $(OUTPUT_DIR)/* $(OBJ_DIR)/*

print-%:
	@echo $($(subst print-,,$@))

