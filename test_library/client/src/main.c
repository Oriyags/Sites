#include "../../../library/sockets_lib.h"
#include "../inc/udp_client.h"
#include "../inc/tcp_client.h"
#include <stdio.h>
#include <string.h>

int main() {
    const char *host = "127.0.0.1";
    int port = 8080;

    // Test TCP
    int my_socket = my_connect(host, port);
    if (my_socket >= 0) {
        const char *message = "Hello, TCP!";
        my_send(my_socket, message, strlen(message));

        char buffer[1024];
        int received = my_receive(my_socket, buffer, sizeof(buffer));
        if (received > 0) {
            buffer[received] = '\0';
            printf("Received from TCP server: %s\n", buffer);
        }
        my_close(my_socket);
    }

    // Test UDP
    int my_socket = my_connect(host, port);
    if (my_socket >= 0) {
        const char *message = "Hello, UDP!";
        my_send(my_socket, message, strlen(message));

        char buffer[1024];
        int received = my_receive(my_socket, buffer, sizeof(buffer));
        if (received > 0) {
            buffer[received] = '\0';
            printf("Received from UDP server: %s\n", buffer);
        }
        my_close(my_socket);
    }
    
    return 0;
}