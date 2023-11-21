CC = gcc
CFLAGS = -lm

SRC_DIR = source
LIB_DIR = lib
BUILD_DIR = build
OUTPUT = Eval
CFILES = $(wildcard *.c) $(wildcard $(SRC_DIR)/*.c) $(wildcard $(LIB_DIR)/*.c)

all: build
	gcc -o $(BUILD_DIR)/$(OUTPUT) $(CFLAGS) $(CFILES)

build:
	mkdir $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

