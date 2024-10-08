#if !defined(TCP_CLIENT_H)
#define TCP_CLIENT_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int my_connect(const char *host, int port);
int my_send(int sockfd, const char *data, int len);
int my_receive(int sockfd, char *buffer, int buffer_len);
void my_close(int sockfd);

#endif