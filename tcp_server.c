#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_fd, new_socket;                   // Variables to store the file descriptors
    struct sockaddr_in address;                  // Structure to hold the server address information
    int addr_len = sizeof(address);              // Variable to store the size of the address structure
    char buffer[1024] = {0};                     // Buffer to store the data received from the client, initialized to zero
    const char *hello = "Hello from server";     // Message sent to the client

    // Creating a socket using IPv4
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");                 // Print an error message
        exit(EXIT_FAILURE);                      // Exit the program
    }

    address.sin_family = AF_INET;                // Set the address family to IPv4
    address.sin_addr.s_addr = INADDR_ANY;        // Accept connections from any IP address
    address.sin_port = htons(8080);              // Set the port number to 8080, converting it to network byte order

    // Bind the socket to the specified IP address and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");                   // Print an error message
        close(server_fd);                        // Close the socket
        exit(EXIT_FAILURE);                      // Exit the program
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {              // Listen for up to 3 pending connections
        perror("listen");                        // Print an error message
        close(server_fd);                        // Close the socket
        exit(EXIT_FAILURE);                      // Exit the program
    }

    // Accept an incoming connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addr_len)) < 0) {
        perror("accept");                        // Print an error message
        close(server_fd);                        // Close the server socket
        exit(EXIT_FAILURE);                      // Exit the program
    }

    // Read data from the client
    read(new_socket, buffer, 1024);              // Read up to 1024 bytes from the client into the buffer
    printf("Message from client: %s\n", buffer); // Print the message received from the client

    // Send a message to the client
    send(new_socket, hello, strlen(hello), 0);   // Send the message to the client
    printf("Hello message sent\n");              // Print confirmation that the message was sent

    close(new_socket);                           // Close the connection socket
    close(server_fd);                            // Close the server socket
    return 0;                                    // Return 0 to indicate successful execution
}