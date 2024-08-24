#if !defined(UDP_LIB_H)
#define UDP_LIB_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int udp_connect(const char *host, int port);
int udp_send(int sockfd, const char *data, int len);
int udp_receive(int sockfd, char *buffer, int buffer_len);
void udp_close(int sockfd);

#endif