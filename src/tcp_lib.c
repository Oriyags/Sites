#include "tcp_lib.h"   // Include the custom header file for TCP functions
#include <stdio.h>     // Include standard I/O for debugging and error messages
#include <stdlib.h>    // Include standard library for general-purpose functions
#include <string.h>    // Include string library for memory manipulation functions like memset
#include <arpa/inet.h> // Include the definitions for internet operations like `inet_pton`
#include <unistd.h>    // Include POSIX API for functions like `close`

// Establishes a TCP connection to a specified host and port.
int tcp_connect(const char *host, int port) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);  // Create a socket using the IPv4 address family (AF_INET) and the TCP protocol (SOCK_STREAM)
    
    // Check if socket creation failed
    if (sockfd < 0) {
        perror("socket");                          // Print an error message if socket creation failed
        return -1;                                 // Return -1 to indicate an error
    }

    struct sockaddr_in server_addr;                // Define a structure to hold the server address information
    memset(&server_addr, 0, sizeof(server_addr));  // Clear the server_addr structure by setting all bytes to 0
    
    server_addr.sin_family = AF_INET;              // Set the address family to IPv4
    server_addr.sin_port = htons(port);            // Set the server port, converting it to network byte order using `htons`

    // Convert the host IP address from text to binary form and store it in server_addr.sin_addr
    if (inet_pton(AF_INET, host, &server_addr.sin_addr) <= 0) {
        perror("inet_pton");                       // Print an error message if address conversion failed
        close(sockfd);                             // Close the socket as it's no longer needed
        return -1;                                 // Return -1 to indicate an error
    }

    // Connect to the server with the specified address and port
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");                        // Print an error message if the connection failed
        close(sockfd);                            // Close the socket as it's no longer needed
        return -1;                                // Return -1 to indicate an error
    }

    return sockfd;                                 // Return the socket file descriptor for successful connections
}

// Sends data over a connected TCP socket.
int tcp_send(int sockfd, const char *data, int len) {
    return send(sockfd, data, len, 0);             // Send data over the socket, using the default flags (0)
}

// Receives data from a connected TCP socket.
int tcp_receive(int sockfd, char *buffer, int buffer_len) {
    return recv(sockfd, buffer, buffer_len, 0);    // Receive data from the socket, storing it in the provided buffer
}

// Closes the TCP socket.

int tcp_close(int sockfd) {
    return close(sockfd);                          // Close the socket using the POSIX `close` function
}
