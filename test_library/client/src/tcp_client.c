#include "../../../library/sockets_lib.h"
#include "../inc/tcp_client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void tcp_client() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from TCP client";
    char buffer[BUFFER_SIZE] = {0};

    if ((sock = my_socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = my_htons(PORT);
       
    if (my_inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return;
    }

    if (my_connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return;
    }

    my_send(sock, hello, strlen(hello), 0);
    printf("Hello message sent\n");
    int valread = read(sock, buffer, BUFFER_SIZE);
    printf("Received: %s\n", buffer);

    my_close(sock);
}