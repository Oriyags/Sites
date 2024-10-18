#include "../../../library/sockets_lib.h"
#include "../inc/udp_client.h"
#include "../inc/tcp_client.h"
#include <stdio.h>
#include <string.h>

int main() {
    const char *host = "127.0.0.1";
    int port = 8080;

    // Create a sockaddr_in structure for the server address
    struct my_sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = my_htons(port);  // Use my_htons for port conversion
    my_inet_pton(AF_INET, host, &server_addr.sin_addr);  // Use my_inet_pton

    // Try TCP connection first
    int tcp_socket = my_socket(AF_INET, SOCK_STREAM, 0);
    int tcp_connection_successful = 0;  // Flag to indicate TCP success

    if (tcp_socket >= 0) {
        if (my_connect(tcp_socket, (struct my_sockaddr*)&server_addr, sizeof(server_addr)) >= 0) {
            tcp_connection_successful = 1;  // Set flag if TCP connection is successful
            const char *message = "Hello, TCP!";
            if (my_send(tcp_socket, message, strlen(message), 0) < 0) {  // Check if my_send is successful
                my_perror("my_send failed");
            }

            char buffer[1024];
            int received = my_recv(tcp_socket, buffer, sizeof(buffer), 0);  // Use my_recv
            if (received > 0) {
                buffer[received] = '\0';
                printf("Received from TCP server: %s\n", buffer);
            } else {
                my_perror("my_recv failed");
            }
            my_close(tcp_socket);
        } else {
            // If the TCP connection fails, close the socket and set the flag
            my_close(tcp_socket);
            printf("TCP connection failed; switching to UDP.\n");  // Optional debug message
        }
    }

    // Only proceed to UDP if TCP wasn't successful
    if (!tcp_connection_successful) {
        // Create a UDP socket
        int udp_socket = my_socket(AF_INET, SOCK_DGRAM, 0);
        if (udp_socket >= 0) {
            const char *message = "Hello, UDP!";
            // Use my_sendto for sending UDP message
            if (my_sendto(udp_socket, message, strlen(message), 0, (struct my_sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
                my_perror("my_sendto failed");
            } else {
                printf("Message sent to UDP server: %s\n", message);
            }

            char buffer[1024];
            socklen_t addr_len = sizeof(server_addr);
            // Use my_recvfrom for receiving UDP messages
            int received = my_recvfrom(udp_socket, buffer, sizeof(buffer), 0, (struct my_sockaddr*)&server_addr, &addr_len);
            if (received > 0) {
                buffer[received] = '\0';
                printf("Received from UDP server: %s\n", buffer);
            } else {
                my_perror("my_recvfrom failed");
            }
            my_close(udp_socket);
        } else {
            my_perror("my_socket for UDP failed");
        }
    }

    return 0;
}