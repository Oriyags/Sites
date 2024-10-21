#ifndef SOCKETS_LIB_H
#define SOCKETS_LIB_H

#include "socket_management.h"
#include "data_transmission.h"
#include "socket_utils.h"
#include "memory_management.h"
#include "syscall_wrappers.h"

#include <sys/types.h>
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MY_AF_INET 2                          // Address family for IPv4
#define MY_SOCK_STREAM 1                      // Socket type for TCP connections
#define MY_SOCK_DGRAM 2                       // Socket type for UDP connections
#define MY_INET_ADDRSTRLEN 16                 // Length of an IPv4 address in string format
#define MY_INADDR_ANY ((uint32_t)0x00000000)  // Bind to all available interfaces

#define MY_SOL_SOCKET 1
#define MY_SO_REUSEADDR 2
#define MY_SOCK_CLOSED -1

typedef unsigned short my_uint16_t;
typedef unsigned int my_uint32_t;
typedef unsigned int socklen_t;

struct my_in_addr {
    my_uint32_t s_addr;  // 32-bit IPv4 address
};

struct my_sockaddr {
    my_uint16_t sa_family;  // Address family (AF_INET)
    char sa_data[14];       // Address data (14 bytes)
};

struct my_sockaddr_in {
    my_uint16_t sin_family;       // Address family (AF_INET)
    my_uint16_t sin_port;         // Port number
    struct my_in_addr sin_addr;   // IPv4 address
    unsigned char sin_zero[8];    // Padding (zeroed)
};

#endif