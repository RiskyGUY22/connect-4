CC = gcc
CFLAGS = -Wall -Wextra -std=c99
SRCS := $(wildcard src/init/*.c)
OUT_SRC := $(wildcard *.c)
OUT_DIR = out
TARGETS := $(patsubst %.c,$(OUT_DIR)/%,$(SRCS))

all: $(TARGETS)

$(OUT_DIR)/%: %.c | $(OUT_DIR)
	$(CC) $(CFLAGS) -o $@ $<

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

clean:
	rm -rf $(OUT_DIR)/*

.PHONY: all clean
