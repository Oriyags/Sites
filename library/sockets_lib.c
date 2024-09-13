#include "sockets_lib.h"
#include <sys/types.h>
#include <sys/syscall.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

// Define necessary constants and structures
#define AF_INET 2   // Address family for IPv4
#define INET_ADDRSTRLEN 16

// Define struct in_addr manually
struct in_addr {
    unsigned long s_addr; // Use a single unsigned long to represent the address
};

// Define struct sockaddr_in manually for IPv4
struct sockaddr_in {
    short sin_family;
    unsigned short sin_port;
    struct in_addr sin_addr;
    char sin_zero[8];
};

// Helper function to print errors
void my_perror(const char *s) {
    if (s && *s) {
        write(STDERR_FILENO, s, strlen(s));
        write(STDERR_FILENO, ": ", 2);
    }
    const char *error_message = strerror(errno);
    write(STDERR_FILENO, error_message, strlen(error_message));
    write(STDERR_FILENO, "\n", 1);
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
    if (domain != AF_INET) {
        my_perror("my_socket - Only AF_INET is supported");
        return -1;
    }
    int sockfd = syscall(__NR_socket, domain, type, protocol);
    if (sockfd < 0) {
        my_perror("my_socket");
    }
    return sockfd;
}

int my_bind(int sockfd, const void *addr, uint32_t addrlen) {
    int result = syscall(__NR_bind, sockfd, addr, addrlen);
    if (result < 0) {
        my_perror("my_bind");
    }
    return result;
}

int my_listen(int sockfd, int backlog) {
    int result = syscall(__NR_listen, sockfd, backlog);
    if (result < 0) {
        my_perror("my_listen");
    }
    return result;
}

int my_accept(int sockfd, void *addr, uint32_t *addrlen) {
    int new_sockfd = syscall(__NR_accept, sockfd, addr, addrlen);
    if (new_sockfd < 0) {
        my_perror("my_accept");
    }
    return new_sockfd;
}

int my_connect(int sockfd, const void *addr, uint32_t addrlen) {
    int result = syscall(__NR_connect, sockfd, addr, addrlen);
    if (result < 0) {
        my_perror("my_connect");
    }
    return result;
}

int my_close(int sockfd) {
    int result = syscall(__NR_close, sockfd);
    if (result < 0) {
        my_perror("my_close");
    }
    return result;
}

// Data Transmission Functions
ssize_t my_send(int sockfd, const void *buf, size_t len, int flags) {
    ssize_t result = syscall(__NR_sendto, sockfd, buf, len, flags, NULL, 0);
    if (result < 0) {
        my_perror("my_send");
    }
    return result;
}

ssize_t my_recv(int sockfd, void *buf, size_t len, int flags) {
    ssize_t result = syscall(__NR_recvfrom, sockfd, buf, len, flags, NULL, NULL);
    if (result < 0) {
        my_perror("my_recv");
    }
    return result;
}

ssize_t my_sendto(int sockfd, const void *buf, size_t len, int flags, const void *dest_addr, uint32_t addrlen) {
    ssize_t result = syscall(__NR_sendto, sockfd, buf, len, flags, dest_addr, addrlen);
    if (result < 0) {
        my_perror("my_sendto");
    }
    return result;
}

ssize_t my_recvfrom(int sockfd, void *buf, size_t len, int flags, void *src_addr, uint32_t *addrlen) {
    ssize_t result = syscall(__NR_recvfrom, sockfd, buf, len, flags, src_addr, addrlen);
    if (result < 0) {
        my_perror("my_recvfrom");
    }
    return result;
}

// IPv4 support for inet_pton
int my_inet_pton(int af, const char *src, void *dst) {
    if (af == AF_INET) {
        struct in_addr *addr = (struct in_addr *)dst;
        unsigned int a, b, c, d;
        if (sscanf(src, "%u.%u.%u.%u", &a, &b, &c, &d) == 4) {
            addr->s_addr = (a << 24) | (b << 16) | (c << 8) | d;
            return 1;
        }
        my_perror("my_inet_pton - Invalid IPv4 address format");
        return 0;
    }
    my_perror("my_inet_pton - Only AF_INET is supported");
    return -1;
}

// IPv4 support for inet_ntop
const char *my_inet_ntop(int af, const void *src, char *dst, uint32_t size) {
    if (af == AF_INET) {
        const struct in_addr *addr = (const struct in_addr *)src;
        if (size < INET_ADDRSTRLEN) {
            my_perror("my_inet_ntop - Insufficient buffer size");
            return NULL;
        }
        snprintf(dst, size, "%u.%u.%u.%u",
                 (addr->s_addr >> 24) & 0xFF,
                 (addr->s_addr >> 16) & 0xFF,
                 (addr->s_addr >> 8) & 0xFF,
                 addr->s_addr & 0xFF);
        return dst;
    }
    my_perror("my_inet_ntop - Only AF_INET is supported");
    return NULL;
}

// Socket Option Management
int my_setsockopt(int sockfd, int level, int optname, const void *optval, uint32_t optlen) {
    int result = syscall(__NR_setsockopt, sockfd, level, optname, optval, optlen);
    if (result < 0) {
        my_perror("my_setsockopt");
    }
    return result;
}

int my_getsockopt(int sockfd, int level, int optname, void *optval, uint32_t *optlen) {
    int result = syscall(__NR_getsockopt, sockfd, level, optname, optval, optlen);
    if (result < 0) {
        my_perror("my_getsockopt");
    }
    return result;
}

// Control non-blocking mode using fcntl (file control)
int my_fcntl(int sockfd, int cmd, long arg) {
    int result = syscall(__NR_fcntl, sockfd, cmd, arg);
    if (result < 0) {
        my_perror("my_fcntl");
    }
    return result;
}