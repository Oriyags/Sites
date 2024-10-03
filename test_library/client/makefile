# Define main directories
SRC_DIR := src
BIN_DIR := bin
INC_DIR := inc
LIB_DIR := ../../library

# Find C sources and object files
SRCS := $(shell find $(SRC_DIR) -name '*.c') $(LIB_DIR)/sockets_lib.c
OBJS := $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRCS))
OBJS := $(patsubst $(LIB_DIR)/%.c, $(BIN_DIR)/%.o, $(OBJS))

# Define compiler settings
CC      := gcc
CFLAGS  := -I$(INC_DIR) -I$(LIB_DIR) -g -Wall -Wextra
BIN_OUT := $(BIN_DIR)/Program.elf

_all: $(BIN_OUT)

# Compile source files to objects
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BIN_DIR)/%.o: $(LIB_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

# Link objects to create final image
$(BIN_OUT): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Clean binary
clean:
	rm -rf $(BIN_DIR)

# Execute program
run: $(BIN_OUT)
	$< ${ARGS}

# Recompile program
re: clean $(BIN_OUT)

# Recompile program and execute
rer: clean run

# Recompile program and execute via a debugger
rerd: clean rund

# Execute program via a debugger
rund: $(BIN_OUT)
	gdb -ex 'layout src' ${GDBF} --args $< ${ARGS}

.PHONY: _all clean run re rer rerd rund
