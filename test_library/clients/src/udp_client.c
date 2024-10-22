#include "udp_client.h"
#include "sockets_lib.h"
#include <stdio.h>
#include <string.h>

#define PORT 8080

// Utility function to handle UDP sending and receiving
int udp_client() {
    int sockfd;
    struct my_sockaddr_in servaddr, src_addr;
    char buffer[1024] = {0};
    const char *message = "Hello from UDP client";
    socklen_t addrlen = sizeof(src_addr);  // To store the length of the address

    // Create socket
    if ((sockfd = my_socket(MY_AF_INET, MY_SOCK_DGRAM, 0)) < 0) {
        my_perror("Socket creation failed");
        return -1;
    }

    my_memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = MY_AF_INET;
    servaddr.sin_port = my_htons(PORT);
    my_inet_pton(MY_AF_INET, "127.0.0.1", &servaddr.sin_addr); // Correctly set server address

    // Send message
    my_sendto(sockfd, message, strlen(message), 0, (struct my_sockaddr *)&servaddr, sizeof(servaddr));
    printf("UDP client: Message sent\n");

    // Receive response
    if (my_recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct my_sockaddr *)&src_addr, &addrlen) < 0) {
        my_perror("Receive failed");
        return -1;
    }
    printf("UDP client: Message from server: %s\n", buffer);

    // Close socket
    my_close(sockfd);
    return 0;
}