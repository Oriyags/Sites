#include "udp_client.h"
#include "sockets_lib.h"
#include <stdio.h>
#include <string.h>

#define PORT 8080

// Utility function to handle UDP sending and receiving
int udp_client() {
    int sockfd;
    struct my_sockaddr_in servaddr;
    char buffer[1024] = {0};
    const char *message = "Hello from UDP client";

    // Create socket
    if ((sockfd = my_socket(MY_AF_INET, MY_SOCK_DGRAM, 0)) < 0) {
        my_perror("Socket creation failed");
        return -1;
    }

    my_memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = MY_AF_INET;
    servaddr.sin_port = my_htons(PORT);

    // Send message
    my_sendto(sockfd, message, strlen(message), 0, (struct my_sockaddr *)&servaddr, sizeof(servaddr));
    printf("UDP client: Message sent\n");

    // Receive response
    my_recvfrom(sockfd, buffer, 1024, 0, NULL, NULL);
    printf("UDP client: Message from server: %s\n", buffer);

    // Close socket
    my_close(sockfd);
    return 0;
}