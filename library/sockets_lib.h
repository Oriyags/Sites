#ifndef SOCKETS_LIB_H
#define SOCKETS_LIB_H

#include <sys/types.h>
#include <stdint.h>
#include <stddef.h>

#define AF_INET 2
#define SOCK_STREAM 1    // Type for TCP
#define SOCK_DGRAM 2     // Type for UDP
#define INET_ADDRSTRLEN 16

struct in_addr {
    unsigned long s_addr;
};

struct sockaddr_in {
    short sin_family;
    unsigned short sin_port;
    struct in_addr sin_addr;
    char sin_zero[8];
};


void *my_memset(void *s, int c, size_t n);

uint32_t my_htonl(uint32_t hostlong);
uint16_t my_htons(uint16_t hostshort);
uint32_t my_ntohl(uint32_t netlong);
uint16_t my_ntohs(uint16_t netshort);

int my_socket(int domain, int type, int protocol);
int my_bind(int sockfd, const void *addr, uint32_t addrlen);
int my_listen(int sockfd, int backlog);
int my_accept(int sockfd, void *addr, uint32_t *addrlen);
int my_connect(int sockfd, const void *addr, uint32_t addrlen);
int my_close(int sockfd);

ssize_t my_send(int sockfd, const void *buf, size_t len, int flags);
ssize_t my_recv(int sockfd, void *buf, size_t len, int flags);
ssize_t my_sendto(int sockfd, const void *buf, size_t len, int flags, const void *dest_addr, uint32_t addrlen);
ssize_t my_recvfrom(int sockfd, void *buf, size_t len, int flags, void *src_addr, uint32_t *addrlen);

int my_inet_pton(int af, const char *src, void *dst);
const char *my_inet_ntop(int af, const void *src, char *dst, uint32_t size);

int my_setsockopt(int sockfd, int level, int optname, const void *optval, uint32_t optlen);
int my_getsockopt(int sockfd, int level, int optname, void *optval, uint32_t *optlen);

int my_fcntl(int sockfd, int cmd, long arg);

#endif