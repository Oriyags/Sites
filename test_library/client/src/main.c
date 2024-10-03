#include "../../../library/sockets_lib.h"
#include "../inc/udp_client.h"
#include "../inc/tcp_client.h"
#include <stdio.h>
#include <string.h>

int main() {
    const char *host = "127.0.0.1";
    int port = 8080;

    // Test TCP
    int tcp_socket = tcp_connect(host, port);
    if (tcp_socket >= 0) {
        const char *message = "Hello, TCP!";
        tcp_send(tcp_socket, message, strlen(message));

        char buffer[1024];
        int received = tcp_receive(tcp_socket, buffer, sizeof(buffer));
        if (received > 0) {
            buffer[received] = '\0';
            printf("Received from TCP server: %s\n", buffer);
        }
        tcp_close(tcp_socket);
    }

    // Test UDP
    int udp_socket = udp_connect(host, port);
    if (udp_socket >= 0) {
        const char *message = "Hello, UDP!";
        udp_send(udp_socket, message, strlen(message));

        char buffer[1024];
        int received = udp_receive(udp_socket, buffer, sizeof(buffer));
        if (received > 0) {
            buffer[received] = '\0';
            printf("Received from UDP server: %s\n", buffer);
        }
        udp_close(udp_socket);
    }
    
    return 0;
}
