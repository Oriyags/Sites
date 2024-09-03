#include "sockets_lib.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A structure to hold socket information
typedef struct {
    int domain;
    int type;
    int protocol;
    int fd;
    struct sockaddr_in addr;
} my_socket_t;

#define MAX_SOCKETS 1024
static my_socket_t socket_table[MAX_SOCKETS];  // Simple table to hold the sockets

static int next_fd = 0;                        // Simple counter to mimic file descriptors

// Initialize the socket table
static void init_socket_table() {
    memset(socket_table, 0, sizeof(socket_table));
}

// Find a free slot in the socket table
static int allocate_socket() {
    for (int i = 0; i < MAX_SOCKETS; i++) {
        if (socket_table[i].fd == 0) {
            socket_table[i].fd = ++next_fd;
            return i;
        }
    }
    return -1;                                 // No available slots
}

// Create a socket
int my_socket(int domain, int type, int protocol) {
    int index = allocate_socket();
    if (index < 0) {
        errno = ENOMEM;
        perror("Socket allocation failed");
        return MY_SOCKET_ERROR;
    }

    socket_table[index].domain = domain;
    socket_table[index].type = type;
    socket_table[index].protocol = protocol;

    return socket_table[index].fd;
}

// Bind a socket to an address
int my_bind(int fd, const struct sockaddr *addr, socklen_t addrlen) {
    // Find the socket in the table
    my_socket_t *sock = NULL;
    for (int i = 0; i < MAX_SOCKETS; i++) {
        if (socket_table[i].fd == fd) {
            sock = &socket_table[i];
            break;
        }
    }

    if (sock == NULL) {
        errno = EBADF;
        perror("Invalid socket descriptor");
        return MY_SOCKET_ERROR;
    }

    // Store the address information in the socket
    memcpy(&sock->addr, addr, addrlen);
    return MY_SOCKET_SUCCESS;
}

// Mark the socket as passive (conceptual, no real network interaction)
int my_listen(int fd, int backlog) {
    // No-op in this conceptual implementation
    return MY_SOCKET_SUCCESS;
}

// Accept an incoming connection (conceptual, no real network interaction)
int my_accept(int fd, struct sockaddr *addr, socklen_t *addrlen) {
    // No-op in this conceptual implementation, just return a new socket descriptor
    int new_fd = my_socket(AF_INET, SOCK_STREAM, 0);
    if (new_fd < 0) {
        return MY_SOCKET_ERROR;
    }
    // Mocking the accept, just copying the address from the original socket
    if (addr && addrlen) {
        for (int i = 0; i < MAX_SOCKETS; i++) {
            if (socket_table[i].fd == fd) {
                memcpy(addr, &socket_table[i].addr, *addrlen);
                break;
            }
        }
    }
    return new_fd;
}

// Connect to a server (conceptual, no real network interaction)
int my_connect(int fd, const struct sockaddr *addr, socklen_t addrlen) {
    // No-op in this conceptual implementation
    return MY_SOCKET_SUCCESS;
}

// Send data over the socket (conceptual, no real network interaction)
ssize_t my_send(int fd, const void *buff, size_t len, int flags) {
    // No-op in this conceptual implementation, just return the length of the data
    return len;
}

// Receive data from the socket (conceptual, no real network interaction)
ssize_t my_recv(int fd, void *buff, size_t len, int flags) {
    // No-op in this conceptual implementation, just return 0 to indicate end-of-file
    return 0;
}

// Close the socket
int my_close(int fd) {
    // Find the socket in the table and clear it
    for (int i = 0; i < MAX_SOCKETS; i++) {
        if (socket_table[i].fd == fd) {
            memset(&socket_table[i], 0, sizeof(my_socket_t));
            return MY_SOCKET_SUCCESS;
        }
    }
    errno = EBADF;
    perror("Invalid socket descriptor");
    return MY_SOCKET_ERROR;
}