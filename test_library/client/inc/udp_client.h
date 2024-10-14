#if !defined(UDP_CLIENT_H)
#define UDP_CLIENT_H

#include "udp_client.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int my_close(int sockfd);

#endif