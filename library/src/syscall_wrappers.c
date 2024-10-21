#include "syscall_wrappers.h"

// Inline function to make a syscall for socket
inline int sys_socket(int domain, int type, int protocol) {
    return syscall(__NR_socket, domain, type, protocol);   // Perform a syscall to create a socket
}

// Inline function to make a syscall for bind
inline int sys_bind(int sockfd, const struct my_sockaddr *addr, uint32_t addrlen) {
    return syscall(__NR_bind, sockfd, addr, addrlen);   // Perform a syscall to bind a socket to an address
}

// Inline function to make a syscall for listen
inline int sys_listen(int sockfd, int backlog) {
    return syscall(__NR_listen, sockfd, backlog);   // Perform a syscall to listen for incoming connections
}

// Inline function to make a syscall for accept
inline int sys_accept(int sockfd, void *addr, uint32_t *addrlen) {
    return syscall(__NR_accept, sockfd, addr, addrlen);   // Perform a syscall to accept an incoming connection
}

// Inline function to make a syscall for connect
inline int sys_connect(int sockfd, const struct my_sockaddr *addr, uint32_t addrlen) {
    return syscall(__NR_connect, sockfd, addr, addrlen);   // Perform a syscall to connect a socket to a remote address
}

// Inline function to make a syscall for send
inline ssize_t sys_send(int sockfd, const void *buf, size_t len, int flags) {
    return syscall(__NR_sendto, sockfd, buf, len, flags);   // Perform a syscall to send data on a socket
}

// Inline function to make a syscall for recv
inline ssize_t sys_recv(int sockfd, void *buf, size_t len, int flags) {
    return syscall(__NR_recvfrom, sockfd, buf, len, flags, NULL, NULL);   // Perform a syscall to receive data on a socket
}

// Inline function to make a syscall for close
inline int sys_close(int sockfd) {
    return syscall(__NR_close, sockfd);   // Perform a syscall to close a socket
}

// Inline function to make a syscall for sendto
inline ssize_t sys_sendto(int sockfd, const void *buf, size_t len, int flags, const struct my_sockaddr *dest_addr, socklen_t addrlen) {
    return syscall(__NR_sendto, sockfd, buf, len, flags, dest_addr, addrlen);   // Perform a syscall to send data to a specific address
}

// Inline function to make a syscall for recvfrom
inline ssize_t sys_recvfrom(int sockfd, void *buf, size_t len, int flags, struct my_sockaddr *src_addr, socklen_t *addrlen) {
    return syscall(__NR_recvfrom, sockfd, buf, len, flags, src_addr, addrlen);   // Perform a syscall to receive data from a specific address
}

// Close a socket
int my_close(int sockfd) {
    int result = sys_close(sockfd);   // Call syscall to close the socket
    if (result < 0) {
        my_perror("my_close");  // Print error message if close fails
    }
    return result;  // Return result of close operation
}