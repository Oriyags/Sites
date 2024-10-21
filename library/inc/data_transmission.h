#ifndef DATA_TRANSMISSION_H
#define DATA_TRANSMISSION_H

#include "data_transmission.h"
#include "sockets_lib.h"
#include <sys/syscall.h>
#include <errno.h>
#include <unistd.h>

ssize_t my_send(int sockfd, const void *buf, size_t len, int flags);
ssize_t my_recv(int sockfd, void *buf, size_t len, int flags);
ssize_t my_sendto(int sockfd, const void *buf, size_t len, int flags, const struct my_sockaddr *dest_addr, socklen_t addrlen);
ssize_t my_recvfrom(int sockfd, void *buf, size_t len, int flags, struct my_sockaddr *src_addr, socklen_t *addrlen);

#endif