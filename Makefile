# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -I src/includes

# Directories
SRC_DIR = src
OUT_DIR = out

# Find all C source files in the src directory
SRCS = $(shell find $(SRC_DIR) -name '*.c')

# Generate object file names from source files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OUT_DIR)/%.o)

# Output executable
TARGET = $(OUT_DIR)/Image

# Default target
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJS)
	@mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Compile source files into object files
$(OUT_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -rf $(OUT_DIR) $(TARGET)

.PHONY: all clean
