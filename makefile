CC = gcc
CFLAGS = -Wall -Iinc  # Add -Iinc to tell the compiler to look in the 'inc' directory for headers
BIN_DIR = bin

all: $(BIN_DIR)/tcp_lib.o $(BIN_DIR)/udp_lib.o

$(BIN_DIR)/tcp_lib.o: src/tcp_lib.c inc/tcp_lib.h
	@mkdir -p $(BIN_DIR)  # Create the bin directory if it doesn't exist
	$(CC) $(CFLAGS) -c src/tcp_lib.c -o $(BIN_DIR)/tcp_lib.o

$(BIN_DIR)/udp_lib.o: src/udp_lib.c inc/udp_lib.h
	@mkdir -p $(BIN_DIR)  # Create the bin directory if it doesn't exist
	$(CC) $(CFLAGS) -c src/udp_lib.c -o $(BIN_DIR)/udp_lib.o

clean:
	rm -rf $(BIN_DIR) main
