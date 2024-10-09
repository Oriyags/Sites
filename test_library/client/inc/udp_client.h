#if !defined(UDP_CLIENT_H)
#define UDP_CLIENT_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int my_sendto(int sockfd, const char *data, int len);
int my_recvfrom(int sockfd, char *buffer, int buffer_len);
void my_close(int sockfd);

#endif