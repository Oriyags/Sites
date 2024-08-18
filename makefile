CC = gcc
CFLAGS = -Wall

all: main

main: main.c tcp_lib.o udp_lib.o
	$(CC) $(CFLAGS) -o main main.c tcp_lib.o udp_lib.o

tcp_lib.o: tcp_lib.c tcp_lib.h
	$(CC) $(CFLAGS) -c tcp_lib.c

udp_lib.o: udp_lib.c udp_lib.h
	$(CC) $(CFLAGS) -c udp_lib.c

clean:
	rm -f *.o main
