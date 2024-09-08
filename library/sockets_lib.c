#include "sockets_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/syscall.h>

// Helper function to print errors
void my_perror(const char *s) {
    perror(s);
}

// Memory Functions
void *my_memset(void *s, int c, size_t n) {
    unsigned char *p = s;
    while (n--) {
        *p++ = (unsigned char)c;
    }
    return s;
}

// Byte Order Functions
uint32_t my_htonl(uint32_t hostlong) {
    return ((hostlong & 0xff) << 24) |
           ((hostlong & 0xff00) << 8) |
           ((hostlong & 0xff0000) >> 8) |
           ((hostlong & 0xff000000) >> 24);
}

uint16_t my_htons(uint16_t hostshort) {
    return (hostshort >> 8) | (hostshort << 8);
}

uint32_t my_ntohl(uint32_t netlong) {
    return my_htonl(netlong);
}

uint16_t my_ntohs(uint16_t netshort) {
    return my_htons(netshort);
}

// Socket Management Functions
int my_socket(int domain, int type, int protocol) {
    // Use system call to create a socket descriptor
    int sockfd = syscall(__NR_socket, domain, type, protocol);
    if (sockfd < 0) {
        my_perror("my_socket");
    }
    return sockfd;
}

int my_bind(int sockfd, const void *addr, uint32_t addrlen) {
    // Use system call to bind the socket
    int result = syscall(__NR_bind, sockfd, addr, addrlen);
    if (result < 0) {
        my_perror("my_bind");
    }
    return result;
}

int my_listen(int sockfd, int backlog) {
    // Use system call to listen on the socket
    int result = syscall(__NR_listen, sockfd, backlog);
    if (result < 0) {
        my_perror("my_listen");
    }
    return result;
}

int my_accept(int sockfd, void *addr, uint32_t *addrlen) {
    // Use system call to accept a connection
    int new_sockfd = syscall(__NR_accept, sockfd, addr, addrlen);
    if (new_sockfd < 0) {
        my_perror("my_accept");
    }
    return new_sockfd;
}

int my_connect(int sockfd, const void *addr, uint32_t addrlen) {
    // Use system call to connect the socket
    int result = syscall(__NR_connect, sockfd, addr, addrlen);
    if (result < 0) {
        my_perror("my_connect");
    }
    return result;
}

int my_close(int sockfd) {
    // Use system call to close the socket
    int result = syscall(__NR_close, sockfd);
    if (result < 0) {
        my_perror("my_close");
    }
    return result;
}

// Data Transmission Functions
ssize_t my_send(int sockfd, const void *buf, size_t len, int flags) {
    // Use system call to send data
    ssize_t result = syscall(__NR_sendto, sockfd, buf, len, flags, NULL, 0);
    if (result < 0) {
        my_perror("my_send");
    }
    return result;
}

ssize_t my_recv(int sockfd, void *buf, size_t len, int flags) {
    // Use system call to receive data
    ssize_t result = syscall(__NR_recvfrom, sockfd, buf, len, flags, NULL, NULL);
    if (result < 0) {
        my_perror("my_recv");
    }
    return result;
}

ssize_t my_sendto(int sockfd, const void *buf, size_t len, int flags, const void *dest_addr, uint32_t addrlen) {
    // Use system call to send data to a specific address
    ssize_t result = syscall(__NR_sendto, sockfd, buf, len, flags, dest_addr, addrlen);
    if (result < 0) {
        my_perror("my_sendto");
    }
    return result;
}

ssize_t my_recvfrom(int sockfd, void *buf, size_t len, int flags, void *src_addr, uint32_t *addrlen) {
    // Use system call to receive data from a specific address
    ssize_t result = syscall(__NR_recvfrom, sockfd, buf, len, flags, src_addr, addrlen);
    if (result < 0) {
        my_perror("my_recvfrom");
    }
    return result;
}

// Network Utility Functions
int my_inet_pton(int af, const char *src, void *dst) {
    // Convert IP addresses from text to binary form
    struct in_addr addr;
    int result = inet_pton(af, src, &addr);
    if (result == 1) {
        my_memset(dst, 0, sizeof(struct in_addr));
        my_memcpy(dst, &addr, sizeof(struct in_addr));
    } else if (result == 0) {
        my_perror("my_inet_pton - Invalid address format");
    } else {
        my_perror("my_inet_pton");
    }
    return result;
}

const char *my_inet_ntop(int af, const void *src, char *dst, uint32_t size) {
    // Convert IP addresses from binary to text form
    const char *result = inet_ntop(af, src, dst, size);
    if (result == NULL) {
        my_perror("my_inet_ntop");
    }
    return result;
}