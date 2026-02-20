CC = gcc
CFLAGS = -I./src/headers -Wall -Wextra -O3 -lraylib 
LFLAGS = -lm


SRC_DIR = src
BASE_DIR = $(SRC_DIR)/base
IMPL_DIR = $(SRC_DIR)/impl
HEADER_DIR = $(SRC_DIR)/headers
BUILD_DIR = build
RELEASE_DIR = release

SRC_FILES = $(BASE_DIR)/main.c $(wildcard $(IMPL_DIR)/*.c)

OBJ_FILES = $(patsubst (SRC_DIR)/%.c, $(BUILD_DIR)%.o, $(SRC_FILES))

TARGET = $(RELEASE_DIR)/TestProg

all: $(TARGET)

$(TARGET) : $(OBJ_FILES)
		$(CC) $(LFLAGS) $(CFLAGS) $^ -o $@


$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
		@mkdir -p $(dir $@)
		$(CC) $(LFLAGS) $(CFLAGS) -c $< -o $@


clean:
		@rm -rf $(BUILD_DIR)
		@echo "Cleaned build directory"

run: $(TARGET)
		./$(TARGET)

.PHONY: all clean run