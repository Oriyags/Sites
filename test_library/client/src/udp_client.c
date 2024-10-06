#include "sockets_lib.h"
#include "udp_client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Establishes a UDP connection to a specified host and port
int udp_connect(const char *host, int port) {
    int sockfd = my_socket(AF_INET, SOCK_DGRAM, 0);    // create a socket

    // Check if socket creation failed
    if (sockfd < 0) {
        my_perror("socket");                           // Print an error message
        return -1;                                  // Return -1 to indicate an error
    }
    
    struct sockaddr_in server_addr;                 // Define a structure to hold the server address information
    my_memset(&server_addr, 0, sizeof(server_addr));   // Clear the server_addr structure by setting all bytes to 0
    server_addr.sin_family = AF_INET;               // Set the address family to IPv4
    server_addr.sin_port = my_htons(port);             // Set the server port, converting it to network byte order using `htons`

    // Convert the host IP address from text to binary form and store it in server_addr.sin_addr
    if (my_inet_pton(AF_INET, host, &server_addr.sin_addr) <= 0) {
        my_perror("inet_pton");                        // Print an error message
        my_close(sockfd);                              // Close the socket
        return -1;                                  // Return -1 to indicate an error
    }

    // Connect to the server with the specified address and port
    if (my_connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        my_perror("connect");                          // Print an error message
        my_close(sockfd);                              // Close the socket
        return -1;                                  // Return -1 to indicate an error
    }

    return sockfd;
}

// Sends data over a connected UDP socket
int udp_send(int sockfd, const char *data, int len) {
    return my_send(sockfd, data, len, 0);              // Send data over the socket, using the default flags (0)
}

// Receives data from a connected UDP socket
int udp_receive(int sockfd, char *buffer, int buffer_len) {
    return my_recv(sockfd, buffer, buffer_len, 0);     // Receive data from the socket, storing it in the provided buffer
}

// Closes the UDP socket
void udp_close(int sockfd) {
    my_close(sockfd);                                  // Close the socket
}

