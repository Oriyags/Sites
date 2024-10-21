#include "socket_management.h"

// Create a socket
int my_socket(int domain, int type, int protocol) {
    if (domain != MY_AF_INET) {  // Check if the domain is AF_INET (IPv4)
        my_perror("my_socket - Only AF_INET is supported");  // Print error message if domain is not AF_INET
        return -1;  // Return -1 to indicate failure
    }
    int sockfd = sys_socket(domain, type, protocol);  // Call sys_socket to create a socket
    if (sockfd < 0) {
        my_perror("my_socket");  // Print error message if socket creation fails
    }
    return sockfd;  // Return socket file descriptor
}

// Bind a socket
int my_bind(int sockfd, const struct my_sockaddr *addr, uint32_t addrlen) {
    int result = sys_bind(sockfd, (const struct my_sockaddr *)addr, addrlen);  // Call syscall to bind the socket
    if (result < 0) {
        my_perror("my_bind");  // Print error message if bind fails
    }
    return result;  // Return result of bind operation
}

// Listen for incoming connections on a socket
int my_listen(int sockfd, int backlog) {
    int result = sys_listen(sockfd, backlog);   // Call syscall to listen on the socket
    if (result < 0) {
        my_perror("my_listen");  // Print error message if listen fails
    }
    return result;  // Return result of listen operation
}

// Accept an incoming connection on a socket
int my_accept(int sockfd, void *addr, uint32_t *addrlen) {
    int new_sockfd = sys_accept(sockfd, addr, addrlen);   // Call syscall to accept the connection
    if (new_sockfd < 0) {
        my_perror("my_accept");  // Print error message if accept fails
    }
    return new_sockfd;  // Return new socket file descriptor for the accepted connection
}

// Connect to a remote address using a socket
int my_connect(int sockfd, const void *addr, uint32_t addrlen) {
    int result = sys_connect(sockfd, addr, addrlen);   // Call syscall to connect the socket
    if (result < 0) {
        my_perror("my_connect");  // Print error message if connect fails
    }
    return result;  // Return result of connect operation
}
