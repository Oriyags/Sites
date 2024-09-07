#if !defined(SOCKETS_LIB_H)
#define SOCKETS_LIB_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MY_SOCKET_SUCCESS 0
#define MY_SOCKET_ERROR   -1

// Create a socket
int my_socket(int domain, int type, int protocol);

// Bind a socket to an address
int my_bind(int fd, const struct sockaddr *addr, socklen_t addrlen);

// Mark the socket as passive and ready to accept connections
int my_listen(int fd, int backlog);

// Accept an incoming connection
int my_accept(int fd, struct sockaddr *addr, socklen_t *addrlen);

// Connect to a server
int my_connect(int fd, const struct sockaddr *addr, socklen_t addrlen);

// Send data over the socket
ssize_t my_send(int fd, const void *buff, size_t len, int flags);

// Receive data from the socket
ssize_t my_recv(int fd, void *buff, size_t len, int flags);

// Close the socket
int my_close(int fd);

int my_setsockopt(int fd, int level, int optname, const void *optval, socklen_t optlen);

int my_getsockopt(int fd, int level, int optname, void *optval, socklen_t *optlen);

int my_set_timeout(int fd, int sec, int usec);  // Set receive/send timeouts

#endif
