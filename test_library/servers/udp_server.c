#include "sockets_lib.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define PORT 8080

int main() {
    int sockfd;
    struct my_sockaddr_in servaddr, cliaddr;
    uint32_t len;
    char buffer[1024] = {0};
    const char *hello = "Hello from UDP server";

    // Create socket
    if ((sockfd = my_socket(MY_AF_INET, MY_SOCK_DGRAM, 0)) < 0) {
        my_perror("Socket creation failed");
        return -1;
    }

    my_memset(&servaddr, 0, sizeof(servaddr));
    my_memset(&cliaddr, 0, sizeof(cliaddr));

    servaddr.sin_family = MY_AF_INET;
    servaddr.sin_addr.s_addr = my_htonl(MY_INADDR_ANY);
    servaddr.sin_port = my_htons(PORT);

    // Bind the socket
    if (my_bind(sockfd, (struct my_sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        my_perror("Bind failed");
        return -1;
    }

    printf("UDP server is running on port %d...\n", PORT);

    len = sizeof(cliaddr);
    // Receive message from client
    my_recvfrom(sockfd, buffer, 1024, 0, (struct my_sockaddr *)&cliaddr, &len);
    printf("Client message: %s\n", buffer);

    // Send response to client
    my_sendto(sockfd, hello, strlen(hello), 0, (struct my_sockaddr *)&cliaddr, len);
    printf("Hello message sent\n");

    // Close socket
    my_close(sockfd);
    return 0;
}