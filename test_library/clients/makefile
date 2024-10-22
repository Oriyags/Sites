# Compiler and flags
CC = gcc
CFLAGS = -Iinc -I../../library/inc -g -Wall -Wextra

# Directories
BIN_DIR = bin
SRC_DIR = src
LIB_SRC_DIR = ../../library/src
LIB_INC_DIR = ../../library/inc
SERVERS_DIR = ../servers

# Source files for client
SRC_FILES = $(SRC_DIR)/main.c $(SRC_DIR)/tcp_client.c $(SRC_DIR)/udp_client.c
# Source files for servers
SERVERS_SRC_FILES = $(SERVERS_DIR)/tcp_server.c $(SERVERS_DIR)/udp_server.c

# Library source files
LIB_SRC_FILES = $(LIB_SRC_DIR)/sockets_lib.c $(LIB_SRC_DIR)/data_transmission.c $(LIB_SRC_DIR)/memory_management.c \
                $(LIB_SRC_DIR)/socket_management.c $(LIB_SRC_DIR)/socket_utils.c $(LIB_SRC_DIR)/syscall_wrappers.c

# Object files
OBJ_FILES = $(BIN_DIR)/main.o $(BIN_DIR)/tcp_client.o $(BIN_DIR)/udp_client.o
TCP_SERVER_OBJ_FILES = $(BIN_DIR)/tcp_server.o $(LIB_OBJ_FILES)
UDP_SERVER_OBJ_FILES = $(BIN_DIR)/udp_server.o $(LIB_OBJ_FILES)
LIB_OBJ_FILES = $(BIN_DIR)/sockets_lib.o $(BIN_DIR)/data_transmission.o $(BIN_DIR)/memory_management.o \
                $(BIN_DIR)/socket_management.o $(BIN_DIR)/socket_utils.o $(BIN_DIR)/syscall_wrappers.o

# Output binaries for TCP and UDP clients
TCP_CLIENT_OUTPUT = $(BIN_DIR)/tcp_client.elf
UDP_CLIENT_OUTPUT = $(BIN_DIR)/udp_client.elf
# Output binaries for TCP and UDP servers
TCP_SERVER_OUTPUT = $(BIN_DIR)/tcp_server.elf
UDP_SERVER_OUTPUT = $(BIN_DIR)/udp_server.elf

# Target to build all clients and servers
all: $(TCP_CLIENT_OUTPUT) $(UDP_CLIENT_OUTPUT) $(TCP_SERVER_OUTPUT) $(UDP_SERVER_OUTPUT)

# Linking object files to create the TCP client executable
$(TCP_CLIENT_OUTPUT): $(OBJ_FILES) $(LIB_OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $(OBJ_FILES) $(LIB_OBJ_FILES)

# Linking object files to create the UDP client executable
$(UDP_CLIENT_OUTPUT): $(OBJ_FILES) $(LIB_OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $(OBJ_FILES) $(LIB_OBJ_FILES)

# Linking object files to create the TCP server executable
$(TCP_SERVER_OUTPUT): $(BIN_DIR)/tcp_server.o $(LIB_OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $(BIN_DIR)/tcp_server.o $(LIB_OBJ_FILES)

# Linking object files to create the UDP server executable
$(UDP_SERVER_OUTPUT): $(BIN_DIR)/udp_server.o $(LIB_OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $(BIN_DIR)/udp_server.o $(LIB_OBJ_FILES)

# Compiling each client source file into object files
$(BIN_DIR)/main.o: $(SRC_DIR)/main.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BIN_DIR)/tcp_client.o: $(SRC_DIR)/tcp_client.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BIN_DIR)/udp_client.o: $(SRC_DIR)/udp_client.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Compiling each server source file into object files
$(BIN_DIR)/tcp_server.o: $(SERVERS_DIR)/tcp_server.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BIN_DIR)/udp_server.o: $(SERVERS_DIR)/udp_server.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Compiling each library source file into object files
$(BIN_DIR)/sockets_lib.o: $(LIB_SRC_DIR)/sockets_lib.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BIN_DIR)/data_transmission.o: $(LIB_SRC_DIR)/data_transmission.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BIN_DIR)/memory_management.o: $(LIB_SRC_DIR)/memory_management.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BIN_DIR)/socket_management.o: $(LIB_SRC_DIR)/socket_management.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BIN_DIR)/socket_utils.o: $(LIB_SRC_DIR)/socket_utils.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BIN_DIR)/syscall_wrappers.o: $(LIB_SRC_DIR)/syscall_wrappers.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Run the TCP client
run_tcp_client: $(TCP_CLIENT_OUTPUT)
	./$(TCP_CLIENT_OUTPUT)

# Run the UDP client
run_udp_client: $(UDP_CLIENT_OUTPUT)
	./$(UDP_CLIENT_OUTPUT)

# Run the TCP server
run_tcp_server: $(TCP_SERVER_OUTPUT)
	./$(TCP_SERVER_OUTPUT)

# Run the UDP server
run_udp_server: $(UDP_SERVER_OUTPUT)
	./$(UDP_SERVER_OUTPUT)

# Clean up
clean:
	rm -rf $(BIN_DIR)/*.o $(TCP_CLIENT_OUTPUT) $(UDP_CLIENT_OUTPUT) $(TCP_SERVER_OUTPUT) $(UDP_SERVER_OUTPUT)