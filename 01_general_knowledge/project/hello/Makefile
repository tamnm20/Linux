.PHONY: clean

CUR_DIR := .
INC_DIR = $(CUR_DIR)/inc
SRC_DIR = $(CUR_DIR)/src
OBJ_DIR := $(CUR_DIR)/obj
LIB_DIR := $(CUR_DIR)/lib
LIB_STA_DIR := $(LIB_DIR)/static
LIB_SHA_DIR := $(LIB_DIR)/shared
OUTPUT_DIR := $(CUR_DIR)/bin
BIN_DIR := $(OUTPUT_DIR)
SRC_FILES := $(wildcard ./src/*.c)
OBJ_TEMP := $(patsubst ./src/%.c, %.o, $(SRC_FILES))
OBJ_FILES := $(foreach wrd,$(OBJ_TEMP),./obj/$(wrd))

CC := gcc
CFLAGS := -c
PICFLAGS = defined

vpath %.o $(OBJ_DIR)
vpath %.h $(INC_DIR)
vpath %.c $(SRC_DIR)

build_app_static: $(BIN_DIR)/hello_static
build_static_lib: $(LIB_STA_DIR)/libhello_static.a
build_shared_lib: $(LIB_SHA_DIR)/libhello_shared.so
link_static_lib: build_static_lib $(BIN_DIR)/hello_static_stalib
link_shared_lib: $(BIN_DIR)/hello_shared_shalib

run_app_1: build_app_static link_static_lib
	@if test -f "./bin/hello_static" ; then \
		./bin/hello_static; \
	fi
	@if test -f "./bin/hello_static_stalib" ; then \
		./bin/hello_static_stalib; \
	fi
# run_app_2: link_shared_lib
# 	@if test -f "./bin/hello_shared_shalib" ; then \
# 		./bin/hello_shared_shalib; \
# 	fi
run_app_2:  link_shared_lib
	LD_LIBRARY_PATH=$(shell pwd)/lib/shared \
	./bin/hello_shared_shalib

$(BIN_DIR)/hello_static: main.o $(OBJ_TEMP)
	$(CC) -o $@ $(OBJ_FILES) $(OBJ_DIR)/main.o -I$(INC_DIR)

run: $(OUTPUT_DIR)/main
	$(OUTPUT_DIR)/main
$(OUTPUT_DIR)/main: main.o $(OBJ_TEMP)
	$(CC) -o $(OUTPUT_DIR)/main $(OBJ_FILES) $(OBJ_DIR)/main.o


%.o: %.c
ifdef PICFLAGS
	$(CC) -I$(INC_DIR) $(CFLAGS) $< -o $(OBJ_DIR)/$@ -fPIC
else
	$(CC) -I$(INC_DIR) $(CFLAGS) $< -o $(OBJ_DIR)/$@
endif


# Create the static library
$(LIB_STA_DIR)/libhello_static.a: hello_static.o
	ar rcs $@ $(OBJ_DIR)/hello_static.o

# Link statically
$(BIN_DIR)/hello_static_stalib: $(LIB_STA_DIR)/libhello_static.a main.o $(OBJ_TEMP)
	$(CC) $(OBJ_DIR)/main.o $(OBJ_FILES) -L$(LIB_STA_DIR) -lhello_static -o $@

# Create the shared library
hello_shared_fpic: hello_shared.c
	$(CC) $(CFLAGS) -o $(OBJ_DIR)/$@.o $< -I$(INC_DIR) -fPIC

$(LIB_SHA_DIR)/libhello_shared.so: main.o $(OBJ_TEMP)
	$(CC) -shared $(OBJ_DIR)/hello_shared.o -o $@

# #Link dynamically with the shared library
# $(BIN_DIR)/hello_shared_shalib: $(LIB_SHA_DIR)/libhello_shared.so
# 	$(CC) $(OBJ_DIR)/main.o $(OBJ_FILES) -L$(LIB_SHA_DIR) -lhello_shared -o $@
$(BIN_DIR)/hello_shared_shalib:
	$(CC) $(OBJ_DIR)/main.o $(OBJ_FILES) -L$(LIB_SHA_DIR) -lhello_shared -o $@
# LD_LIBRARY_PATH=$(pwd)/lib/shared bin/hello_shared_shalib
# sudo mv /lib/shared/libhello_shared.so /usr/lib
# sudo chmod 755 /usr/lib/libhello_shared.so



readSymbol:
	readelf -sW ./obj/main.o 
clean:
	rm -rf $(OUTPUT_DIR)/* $(OBJ_DIR)/* $(LIB_STA_DIR)/* 
#$(LIB_SHA_DIR)/*

print-%:
	@echo $($(subst print-,,$@))