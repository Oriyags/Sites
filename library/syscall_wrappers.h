#ifndef SYSCALL_WRAPPERS
#define SYSCALL_WRAPPERS

#include "syscall_wrappers.h"
#include "sockets_lib.h"
#include <sys/types.h>
#include <sys/syscall.h>
#include <unistd.h>

// Custom wrapper for system call
int sys_socket(int domain, int type, int protocol);
int sys_bind(int sockfd, const struct my_sockaddr *addr, socklen_t addrlen);
int sys_listen(int sockfd, int backlog);
int sys_accept(int sockfd, void *addr, uint32_t *addrlen);
int sys_connect(int sockfd, const struct my_sockaddr *addr, uint32_t addrlen);
int sys_close(int sockfd);

ssize_t sys_send(int sockfd, const void *buf, size_t len, int flags);
ssize_t sys_recv(int sockfd, void *buf, size_t len, int flags);
ssize_t sys_sendto(int sockfd, const void *buf, size_t len, int flags, const struct my_sockaddr *dest_addr, socklen_t addrlen);
ssize_t sys_recvfrom(int sockfd, void *buf, size_t len, int flags, struct my_sockaddr *src_addr, socklen_t *addrlen);

int my_close(int sockfd);

#endif