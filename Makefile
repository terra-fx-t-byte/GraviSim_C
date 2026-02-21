CC       = gcc
CFLAGS   = -I./src/headers -Wall -Wextra -O3
LDFLAGS  = -lm
LDLIBS   = -lraylib

# Directories
SRC_DIR     = src
BASE_DIR    = $(SRC_DIR)/base
IMPL_DIR    = $(SRC_DIR)/impl
HEADER_DIR  = $(SRC_DIR)/headers
BUILD_DIR   = build
RELEASE_DIR = release

# Source files (main + all implementation files)
SRC_FILES = $(BASE_DIR)/main.c $(wildcard $(IMPL_DIR)/*.c)

# Object files: map src/*.c to build/*.o (preserving subdirectory structure)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

# Target executable
TARGET = $(RELEASE_DIR)/TestProg

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJ_FILES) | $(RELEASE_DIR)
	$(CC) $^ $(LDFLAGS) $(LDLIBS) -o $@

# Compile C sources into objects inside build/
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Create build directory (used as order-only prerequisite)
$(BUILD_DIR):
	@mkdir -p $@

# Create release directory (order-only prerequisite for linking)
$(RELEASE_DIR):
	@mkdir -p $@

# Clean up build artifacts (keep release/ intact)
clean:
	@rm -rf $(BUILD_DIR)
	@echo "Cleaned build directory"

# Run the program
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run