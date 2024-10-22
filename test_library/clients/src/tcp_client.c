#include "sockets_lib.h"
#include "tcp_client.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define PORT 8080

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

    // Prepare the sockaddr_in structure
    my_memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = MY_AF_INET;
    serv_addr.sin_port = my_htons(PORT);
    my_inet_pton(MY_AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    // Connect to server
    if (my_connect(sock, (struct my_sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        my_perror("Connection to server failed");
        return -1;
    } else {
        printf("Connection to server successful!\n");
    }

    // Send message to server
    my_send(sock, message, strlen(message), 0);
    printf("TCP client: Message sent\n");

    // Receive message from server
    int valread = my_recv(sock, buffer, 1024, 0);
    if (valread > 0) {
        printf("TCP client: Message from server: %s\n", buffer);
    } else {
        my_perror("my_recv failed");
    }

    // Close socket
    my_close(sock);

    return 0;
}