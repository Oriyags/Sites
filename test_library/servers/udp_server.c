#include "../library/sockets_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int server_fd;                                      // Variable to store the file descriptor
    struct sockaddr_in server_addr, client_addr;        // Structures to hold the server and client address information
    char buffer[1024];                                  // Buffer to store the data received from the client
    socklen_t addr_len = sizeof(client_addr);           // Variable to store the size of the client address structure
    const char *message = "Hello from UDP server";      // Message to be sent to the client

    // Creating a UDP socket using IPv4
    if ((server_fd = my_socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        my_perror("socket failed");                        // Print an error message if socket creation fails
        exit(EXIT_FAILURE);                             // Exit the program with an error code
    }

    // Set the server address information
    server_addr.sin_family = AF_INET;                   // Set the address family to IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY;           // Accept connections from any IP address
    server_addr.sin_port = my_htons(8081);                 // Set the port number to 8080, converting it to network byte order

    // Bind the socket to the specified IP address and port
    if (my_bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        my_perror("bind failed");                          // Print an error message if binding fails
        my_close(server_fd);                               // Close the socket
        exit(EXIT_FAILURE);                             // Exit the program with an error code
    }

    printf("UDP server is running on port 8080\n");

    // Loop to handle incoming messages
    while (1) {
        // Receive data from the client
        int n = my_recvfrom(server_fd, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr, &addr_len);
        buffer[n] = '\0';                              // Null-terminate the received data

        printf("Received from client: %s\n", buffer);  // Print the message received from the client

        // Send a response back to the client
        my_sendto(server_fd, message, strlen(message), 0, (struct sockaddr *)&client_addr, addr_len);
        printf("Sent response to client: %s\n", message);
    }

    my_close(server_fd);                                 // Close the server socket
    return 0;                                         // Return 0 to indicate successful execution
}
