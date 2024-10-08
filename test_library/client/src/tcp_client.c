#include "tcp_client.h"
#include "sockets_lib.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define PORT 8080

int main() {
    int sock = 0;
    struct my_sockaddr_in serv_addr;
    char buffer[1024] = {0};
    const char *message = "Hello from TCP client";

    if ((sock = my_socket(MY_AF_INET, MY_SOCK_STREAM, 0)) < 0) {
        my_perror("Socket creation failed");
        return -1;
    }

    my_memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = MY_AF_INET;
    serv_addr.sin_port = my_htons(PORT);

    if (my_inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        my_perror("Invalid address/ Address not supported");
        return -1;
    }

    if (my_connect(sock, (struct my_sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        my_perror("Connection failed");
        return -1;
    }

    my_send(sock, message, strlen(message), 0);
    printf("Message sent\n");
    my_recv(sock, buffer, 1024, 0);
    printf("Message from server: %s\n", buffer);

    my_close(sock);
    return 0;
}