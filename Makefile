# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -I src/includes

# Cross-compiler for Windows
CC_WIN = x86_64-w64-mingw32-gcc
CFLAGS_WIN = -Wall -Wextra -I src/includes

# Directories
SRC_DIR = src
OUT_DIR = out

# Find all C source files in the src directory and add to build list
SRCS = $(shell find $(SRC_DIR) -name '*.c')

# Generate object file names from source files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OUT_DIR)/%.o)
OBJS_WIN = $(SRCS:$(SRC_DIR)/%.c=$(OUT_DIR)/%.win.o) # win support

# Output executables
TARGET_LINUX = $(OUT_DIR)/Image
TARGET_WINDOWS = $(OUT_DIR)/Image.exe # win formatted executable

# Default target
all: $(TARGET_LINUX) $(TARGET_WINDOWS)

# Link the object files to create the Linux executable
$(TARGET_LINUX): $(OBJS)
	@mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET_LINUX)

# Link the object files to create the Windows executable
$(TARGET_WINDOWS): $(OBJS_WIN)
	@mkdir -p $(OUT_DIR)
	$(CC_WIN) $(CFLAGS_WIN) $(OBJS_WIN) -o $(TARGET_WINDOWS)

# Compile source files into object files for Linux
$(OUT_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile source files into object files for Windows
$(OUT_DIR)/%.win.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC_WIN) $(CFLAGS_WIN) -c $< -o $@

# Clean builds
clean:
	rm -rf $(OUT_DIR) $(TARGET_LINUX) $(TARGET_WINDOWS)

# Add targets to the phony list
.PHONY: all clean
