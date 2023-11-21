CC = gcc
CFLAGS = -lm

SRC_DIR = source
BUILD_DIR = build
OUTPUT = Eval
CFILES = $(wildcard $(SRC_DIR)/*.c) $(wildcard *.c)

all: build
	gcc -o $(BUILD_DIR)/$(OUTPUT) $(CFLAGS) $(CFILES)

build:
	mkdir $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

