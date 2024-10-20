#if !defined(TCP_CLIENT_H)
#define TCP_CLIENT_H

#include "sockets_lib.h" 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int my_socket(int domain, int type, int protocol);
int my_connect(int sockfd, const void *addr, uint32_t addrlen);
ssize_t my_send(int sockfd, const void *buf, size_t len, int flags);
ssize_t sys_recv(int sockfd, void *buf, size_t len, int flags);
int my_close(int sockfd);

#endif