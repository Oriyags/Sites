#include "sockets_lib.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A structure to hold socket information
typedef struct {
    int domain;                                       // Address domain (e.g., AF_INET for IPv4)
    int type;                                         // Socket type (e.g., SOCK_STREAM for TCP)
    int protocol;                                     // Protocol (usually 0, which lets the system choose the default)
    int fd;                                           // File descriptor (mocked, since this is a conceptual implementation)
    struct sockaddr_in addr;                          // Structure to hold socket address information
} my_socket_t;

#define MAX_SOCKETS 1024                              // Define the maximum number of sockets the system can handle
static my_socket_t socket_table[MAX_SOCKETS];         // Simple table to hold socket information

static int next_fd = 0;                               // Simple counter to mimic file descriptors (increments with each new socket)

// Initialize the socket table
static void init_socket_table() {
    memset(socket_table, 0, sizeof(socket_table));    // Clear the socket table to zero out all entries
}

// Find a free slot in the socket table
static int allocate_socket() {
    for (int i = 0; i < MAX_SOCKETS; i++) {           // Loop through the socket table
        if (socket_table[i].fd == 0) {                // Look for an empty slot (where fd is 0)
            socket_table[i].fd = ++next_fd;           // Assign a new file descriptor (incrementing next_fd)
            return i;                                 // Return the index of the allocated slot
        }
    }
    return -1;                                        // Return -1 if no available slots are found
}

// Create a socket
int my_socket(int domain, int type, int protocol) {
    int index = allocate_socket();                    // Try to allocate a slot in the socket table
    if (index < 0) {                                  // Check if allocation failed
        errno = ENOMEM;                               // Set errno to ENOMEM to indicate memory allocation error
        perror("Socket allocation failed");           // Print an error message
        return MY_SOCKET_ERROR;                       // Return an error code (presumably defined in sockets_lib.h)
    }

    socket_table[index].domain = domain;              // Store the domain in the socket structure
    socket_table[index].type = type;                  // Store the type in the socket structure
    socket_table[index].protocol = protocol;          // Store the protocol in the socket structure

    return socket_table[index].fd;                    // Return the file descriptor of the new socket
}

// Bind a socket to an address
int my_bind(int fd, const struct sockaddr *addr, socklen_t addrlen) {
    my_socket_t *sock = NULL;                         // Pointer to store the socket structure
    for (int i = 0; i < MAX_SOCKETS; i++) {           // Loop through the socket table
        if (socket_table[i].fd == fd) {               // Find the socket with the matching file descriptor
            sock = &socket_table[i];                  // Store the pointer to this socket
            break;                                    // Exit the loop once found
        }
    }

    if (sock == NULL) {                               // Check if the socket was not found
        errno = EBADF;                                // Set errno to EBADF to indicate bad file descriptor
        perror("Invalid socket descriptor");          // Print an error message
        return MY_SOCKET_ERROR;                       // Return an error code
    }

    // Store the address information in the socket
    memcpy(&sock->addr, addr, addrlen);               // Copy the address data into the socket's address field
    return MY_SOCKET_SUCCESS;                         // Return success (presumably defined in sockets_lib.h)
}

// Mark the socket as passive (conceptual, no real network interaction)
int my_listen(int fd, int backlog) {
    // No-op in this conceptual implementation
    return MY_SOCKET_SUCCESS;                         // Return success, no actual operation performed
}

// Accept an incoming connection (conceptual, no real network interaction)
int my_accept(int fd, struct sockaddr *addr, socklen_t *addrlen) {
    // No-op in this conceptual implementation, just return a new socket descriptor
    int new_fd = my_socket(AF_INET, SOCK_STREAM, 0);  // Create a new socket as if accepting a connection
    if (new_fd < 0) {                                 // Check if socket creation failed
        return MY_SOCKET_ERROR;                       // Return an error code
    }
    // Mocking the accept, just copying the address from the original socket
    if (addr && addrlen) {                            // Check if the address pointers are valid
        for (int i = 0; i < MAX_SOCKETS; i++) {       // Loop through the socket table
            if (socket_table[i].fd == fd) {           // Find the original socket
                memcpy(addr, &socket_table[i].addr, *addrlen);  // Copy the address data
                break;                                // Exit the loop once done
            }
        }
    }
    return new_fd;                                    // Return the file descriptor of the new socket
}

// Connect to a server (conceptual, no real network interaction)
int my_connect(int fd, const struct sockaddr *addr, socklen_t addrlen) {
    // No-op in this conceptual implementation
    return MY_SOCKET_SUCCESS;                         // Return success, no actual operation performed
}

// Send data over the socket (conceptual, no real network interaction)
ssize_t my_send(int fd, const void *buff, size_t len, int flags) {
    // No-op in this conceptual implementation, just return the length of the data
    return len;                                       // Simulate a successful send by returning the number of bytes
}

// Receive data from the socket (conceptual, no real network interaction)
ssize_t my_recv(int fd, void *buff, size_t len, int flags) {
    // No-op in this conceptual implementation, just return 0 to indicate end-of-file
    return 0;                                         // Simulate end of data by returning 0
}

// Close the socket
int my_close(int fd) {
    for (int i = 0; i < MAX_SOCKETS; i++) {           // Loop through the socket table
        if (socket_table[i].fd == fd) {               // Find the socket with the matching file descriptor
            memset(&socket_table[i], 0, sizeof(my_socket_t));  // Clear the socket entry
            return MY_SOCKET_SUCCESS;                 // Return success
        }
    }
    errno = EBADF;                                    // Set errno to EBADF to indicate bad file descriptor
    perror("Invalid socket descriptor");              // Print an error message
    return MY_SOCKET_ERROR;                           // Return an error code
}