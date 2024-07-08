# Compiler
CC = gcc

# Remove command
RM = rm -rf

# Compiler flags
CFLAGS = -Wall

# Linker flags
LDFLAGS = -lm

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*/*.c)

# Object files
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))

# Executable files
EXECS = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%, $(SOURCES))

# Default target
.PHONY: all
all: $(EXECS)

# Build each executable
$(BIN_DIR)/%: $(OBJ_DIR)/%.o
	@mkdir -p $(dir $@)
	$(CC) $< -o $@ $(LDFLAGS)

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
.PHONY: clean
clean:
	-$(RM) $(OBJ_DIR)
	-$(RM) $(BIN_DIR)

.PHONY: all clean

