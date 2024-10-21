#ifndef SOCKET_MANAGEMENT_H
#define SOCKET_MANAGEMENT_H

#include "sockets_lib.h"  
#include <sys/syscall.h>  
#include <errno.h>
#include <unistd.h>

int my_socket(int domain, int type, int protocol);
int my_bind(int sockfd, const struct my_sockaddr *addr, uint32_t addrlen);
int my_listen(int sockfd, int backlog);
int my_accept(int sockfd, void *addr, uint32_t *addrlen);
int my_connect(int sockfd, const void *addr, uint32_t addrlen);

#endif