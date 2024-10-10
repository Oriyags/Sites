#include "../../library/sockets_lib.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define PORT 8080

int main() {
    int server_fd, new_socket;
    struct my_sockaddr_in address;
    uint32_t addrlen = sizeof(address);
    char buffer[1024] = {0};
    const char *hello = "Hello from TCP server";

    server_fd = my_socket(MY_AF_INET, MY_SOCK_STREAM, 0);
    if (server_fd == 0) {
        my_perror("Server socket failed");
        return -1;
    }

    my_memset(&address, 0, sizeof(address));
    address.sin_family = MY_AF_INET;
    address.sin_addr.s_addr = my_htonl(MY_INADDR_ANY);
    address.sin_port = my_htons(PORT);

    if (my_bind(server_fd, (struct my_sockaddr *)&address, sizeof(address)) < 0) {
        my_perror("Bind failed");
        return -1;
    }

    if (my_listen(server_fd, 3) < 0) {
        my_perror("Listen failed");
        return -1;
    }

    printf("Waiting for connections...\n");
    new_socket = my_accept(server_fd, (struct my_sockaddr *)&address, &addrlen);
    if (new_socket < 0) {
        my_perror("Accept failed");
        return -1;
    }

    my_recv(new_socket, buffer, 1024, 0);
    printf("Message from client: %s\n", buffer);
    my_send(new_socket, hello, strlen(hello), 0);
    printf("Hello message sent\n");

    my_close(new_socket);
    my_close(server_fd);
    return 0;
}