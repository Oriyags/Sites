#if !defined(TCP_CLIENT_H)
#define TCP_CLIENT_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int tcp_connect(const char *host, int port);
int tcp_send(int sockfd, const char *data, int len);
int tcp_receive(int sockfd, char *buffer, int buffer_len);
void tcp_close(int sockfd);

#endif