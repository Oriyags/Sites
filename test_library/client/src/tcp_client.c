#include "tcp_client.h"
#include "sockets_lib.h"
#include <stdio.h>
#include <string.h>

#define PORT 8080

// Utility function to handle TCP connection, sending, and receiving
int tcp_client() {
    int sock = 0;
    struct my_sockaddr_in serv_addr;
    char buffer[1024] = {0};
    const char *message = "Hello from TCP client";

    // Create socket
    if ((sock = my_socket(MY_AF_INET, MY_SOCK_STREAM, 0)) < 0) {
        my_perror("Socket creation failed");
        return -1;
    }

    my_memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = MY_AF_INET;
    serv_addr.sin_port = my_htons(PORT);

    // Connect to server
    if (my_connect(sock, (struct my_sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        my_perror("Connection failed");
        return -1;
    }

    // Send message
    my_send(sock, message, strlen(message), 0);
    printf("TCP client: Message sent\n");

    // Receive message
    my_recv(sock, buffer, 1024, 0);
    printf("TCP client: Message from server: %s\n", buffer);

    // Close socket
    my_close(sock);
    return 0;
}