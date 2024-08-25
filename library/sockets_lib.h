#if !defined (SOCKETS_LIB_H)
#define SOCKETS_LIB_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MY_SOCKET_SUCCESS 0
#define MY_SOCKET_ERROR   -1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`

// socket
// connect
// send
// recv
// close
// perror
// bind
// memset
// htons
// inet_pton

int my_socket(int domain, int type, int protocol);

int my_bind(int fd, const struct sockaddr *addr, socklen_t addrlen);

int my_listen(int fd, int backlog);

int my_accept(int fd, struct sockaddr *addr, socklen_t *addrlen);

int my_connect(int fd, const struct sockaddr *addr, socklen_t addrlen);

ssize_t my_send(int fd, const void *buff, size_t len, int flags);

ssize_t my_recv(int fd, void *buff, size_t len, int flags);

int my_close(int fd);

#endif