#include "../../../library/sockets_lib.h"
#include "../inc/udp_client.h"
#include "../inc/tcp_client.h"
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>

int main() {
    const char *host = "127.0.0.1";
    int port = 8080;

    // Create a sockaddr_in structure for the server address
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = my_htons(port);  // Use my_htons for port conversion
    my_inet_pton(AF_INET, host, &server_addr.sin_addr);  // Use inet_pton function

    // Test TCP
    int tcp_socket = my_socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_socket >= 0) {
        if (my_connect(tcp_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) >= 0) {
            const char *message = "Hello, TCP!";
            my_send(tcp_socket, message, strlen(message), 0);  // Add 0 as flags

            char buffer[1024];
            int received = my_recv(tcp_socket, buffer, sizeof(buffer), 0);  // Use my_recv
            if (received > 0) {
                buffer[received] = '\0';
                printf("Received from TCP server: %s\n", buffer);
            }
            my_close(tcp_socket);
        }
    }

    // Test UDP
    int udp_socket = my_socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_socket >= 0) {
        if (my_connect(udp_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) >= 0) {
            const char *message = "Hello, UDP!";
            my_send(udp_socket, message, strlen(message), 0);  // Add 0 as flags

            char buffer[1024];
            int received = my_recv(udp_socket, buffer, sizeof(buffer), 0);  // Use my_recv
            if (received > 0) {
                buffer[received] = '\0';
                printf("Received from UDP server: %s\n", buffer);
            }
            my_close(udp_socket);
        }
    }

    return 0;
}
