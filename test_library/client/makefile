# Compiler and flags
CC = gcc
CFLAGS = -Iinc -I../../library -g -Wall -Wextra

# Directories
BIN_DIR = bin
SRC_DIR = src
LIB_DIR = ../../library

# Source files
SRC_FILES = $(SRC_DIR)/main.c $(SRC_DIR)/tcp_client.c $(SRC_DIR)/udp_client.c
OBJ_FILES = $(BIN_DIR)/main.o $(BIN_DIR)/tcp_client.o $(BIN_DIR)/udp_client.o $(BIN_DIR)/sockets_lib.o

# Output binaries for TCP and UDP clients
TCP_OUTPUT = $(BIN_DIR)/tcp_client.elf
UDP_OUTPUT = $(BIN_DIR)/udp_client.elf

# Target to build both TCP and UDP clients
all: $(TCP_OUTPUT) $(UDP_OUTPUT)

# Linking object files to create the TCP executable
$(TCP_OUTPUT): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $(OBJ_FILES)

# Linking object files to create the UDP executable
$(UDP_OUTPUT): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $(OBJ_FILES)

# Compiling each source file into object files
$(BIN_DIR)/main.o: $(SRC_DIR)/main.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BIN_DIR)/tcp_client.o: $(SRC_DIR)/tcp_client.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BIN_DIR)/udp_client.o: $(SRC_DIR)/udp_client.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BIN_DIR)/sockets_lib.o: $(LIB_DIR)/sockets_lib.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Run the TCP client
run_tcp: $(TCP_OUTPUT)
	./$(TCP_OUTPUT)

# Run the UDP client
run_udp: $(UDP_OUTPUT)
	./$(UDP_OUTPUT)

# Clean up
clean:
	rm -rf $(BIN_DIR)/*.o $(TCP_OUTPUT) $(UDP_OUTPUT)
