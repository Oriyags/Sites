#include "sockets_lib.h"
#include <sys/types.h>
#include <sys/syscall.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

/*
BASE
[Hardware <- OS <- syscalls] <- [data <- protocols <- network layers]
*/

// Inline function to make a syscall for socket
inline int sys_socket(int domain, int type, int protocol) {
    return syscall(__NR_socket, domain, type, protocol);   // Perform a syscall to create a socket
}

// Create a socket
int my_socket(int domain, int type, int protocol) {
    if (domain != MY_AF_INET) {  // Check if the domain is AF_INET (IPv4)
        my_perror("my_socket - Only AF_INET is supported");  // Print error message if domain is not AF_INET
        return -1;  // Return -1 to indicate failure
    }
    int sockfd = sys_socket(domain, type, protocol);  // Call sys_socket to create a socket
    if (sockfd < 0) {
        my_perror("my_socket");  // Print error message if socket creation fails
    }
    return sockfd;  // Return socket file descriptor
}

// Inline function to make a syscall for bind
inline int sys_bind(int sockfd, const struct my_sockaddr *addr, uint32_t addrlen) {
    return syscall(__NR_bind, sockfd, addr, addrlen);   // Perform a syscall to bind a socket to an address
}

// Bind a socket
int my_bind(int sockfd, const struct my_sockaddr *addr, uint32_t addrlen) {
    int result = sys_bind(sockfd, (const struct my_sockaddr *)addr, addrlen);  // Call syscall to bind the socket
    if (result < 0) {
        my_perror("my_bind");  // Print error message if bind fails
    }
    return result;  // Return result of bind operation
}

// Inline function to make a syscall for listen
inline int sys_listen(int sockfd, int backlog) {
    return syscall(__NR_listen, sockfd, backlog);   // Perform a syscall to listen for incoming connections
}

// Listen for incoming connections on a socket
int my_listen(int sockfd, int backlog) {
    int result = sys_listen(sockfd, backlog);   // Call syscall to listen on the socket
    if (result < 0) {
        my_perror("my_listen");  // Print error message if listen fails
    }
    return result;  // Return result of listen operation
}

// Inline function to make a syscall for accept
inline int sys_accept(int sockfd, void *addr, uint32_t *addrlen) {
    return syscall(__NR_accept, sockfd, addr, addrlen);   // Perform a syscall to accept an incoming connection
}

// Accept an incoming connection on a socket
int my_accept(int sockfd, void *addr, uint32_t *addrlen) {
    int new_sockfd = sys_accept(sockfd, addr, addrlen);   // Call syscall to accept the connection
    if (new_sockfd < 0) {
        my_perror("my_accept");  // Print error message if accept fails
    }
    return new_sockfd;  // Return new socket file descriptor for the accepted connection
}

// Inline function to make a syscall for connect
inline int sys_connect(int sockfd, const struct my_sockaddr *addr, uint32_t addrlen) {
    return syscall(__NR_connect, sockfd, addr, addrlen);   // Perform a syscall to connect a socket to a remote address
}

// Connect to a remote address using a socket
int my_connect(int sockfd, const void *addr, uint32_t addrlen) {
    int result = sys_connect(sockfd, addr, addrlen);   // Call syscall to connect the socket
    if (result < 0) {
        my_perror("my_connect");  // Print error message if connect fails
    }
    return result;  // Return result of connect operation
}

// Inline function to make a syscall for send
inline ssize_t sys_send(int sockfd, const void *buf, size_t len, int flags) {
    return syscall(__NR_sendto, sockfd, buf, len, flags);   // Perform a syscall to send data on a socket
}

// Send data over a TCP socket
ssize_t my_send(int sockfd, const void *buf, size_t len, int flags) {
    ssize_t result = syscall(__NR_sendto, sockfd, buf, len, flags, NULL, 0);  // Send data using sys_sendto
    if (result < 0) {
        my_perror("my_send");  // Print error message if send fails
    }
    return result;  // Return number of bytes sent
}

// Inline function to make a syscall for recv
inline ssize_t sys_recv(int sockfd, void *buf, size_t len, int flags) {
    return syscall(__NR_recvfrom, sockfd, buf, len, flags, NULL, NULL);   // Perform a syscall to receive data on a socket
}

// Receive data from a TCP socket
ssize_t my_recv(int sockfd, void *buf, size_t len, int flags) {
    ssize_t result = syscall(__NR_recvfrom, sockfd, buf, len, flags, NULL, NULL);  // Receive data using sys_recvfrom
    if (result < 0) {
        my_perror("my_recv");  // Print error message if recv fails
    }
    return result;  // Return number of bytes received
}

// Inline function to make a syscall for close
inline int sys_close(int sockfd) {
    return syscall(__NR_close, sockfd);   // Perform a syscall to close a socket
}

// Close a socket
int my_close(int sockfd) {
    int result = sys_close(sockfd);   // Call syscall to close the socket
    if (result < 0) {
        my_perror("my_close");  // Print error message if close fails
    }
    return result;  // Return result of close operation
}

// Inline function to make a syscall for sendto
inline ssize_t sys_sendto(int sockfd, const void *buf, size_t len, int flags, const struct my_sockaddr *dest_addr, socklen_t addrlen) {
    return syscall(__NR_sendto, sockfd, buf, len, flags, dest_addr, addrlen);   // Perform a syscall to send data to a specific address
}

// Send data to a specific address using a socket
ssize_t my_sendto(int sockfd, const void *buf, size_t len, int flags, const struct my_sockaddr *dest_addr, socklen_t addrlen) {
    ssize_t result = sys_sendto(sockfd, buf, len, flags, dest_addr, addrlen);   // Call syscall to send data
    if (result < 0) {
        my_perror("my_sendto");  // Print error message if sendto fails
    }
    return result;  // Return number of bytes sent
}

// Inline function to make a syscall for recvfrom
inline ssize_t sys_recvfrom(int sockfd, void *buf, size_t len, int flags, struct my_sockaddr *src_addr, socklen_t *addrlen) {
    return syscall(__NR_recvfrom, sockfd, buf, len, flags, src_addr, addrlen);   // Perform a syscall to receive data from a specific address
}

// Receive data from a specific address using a socket
ssize_t my_recvfrom(int sockfd, void *buf, size_t len, int flags, struct my_sockaddr *src_addr, socklen_t *addrlen) {
    ssize_t result = sys_recvfrom(sockfd, buf, len, flags, src_addr, addrlen);   // Call syscall to receive data
    if (result < 0) {
        my_perror("my_recvfrom");  // Print error message if recvfrom fails
    }
    return result;  // Return number of bytes received
}

// Helper function to print errors
void my_perror(const char *s) {
    if (s && *s) { 
        write(STDERR_FILENO, s, strlen(s));   // Print error message prefix to standard error
        write(STDERR_FILENO, ": ", 2);        // Print ": " after the prefix
    } 
    const char *error_message = strerror(errno);   // Get error message string based on errno
    write(STDERR_FILENO, error_message, strlen(error_message));   // Print the error message
    write(STDERR_FILENO, "\n", 1);   // Print newline character
}

// Set a block of memory to a specific value
void *my_memset(void *s, int c, size_t n) {
    unsigned char *p = s;  // Cast pointer to unsigned char for byte-wise operations
    while (n--) {
        *p++ = (unsigned char)c;  // Set each byte in the block to the specified value
    }
    return s;  // Return the pointer to the memory block
}

// Byte Order Functions
// Convert a 32-bit value from host byte order to network byte order (big-endian)
uint32_t my_htonl(uint32_t hostlong) {
    return ((hostlong & 0xff) << 24) |    // Move least significant byte (LSB) to the most significant position
           ((hostlong & 0xff00) << 8) |   // Move second byte from LSB to its proper position
           ((hostlong & 0xff0000) >> 8) | // Move third byte from LSB to its proper position
           ((hostlong & 0xff000000) >> 24); // Move most significant byte (MSB) to the least significant position
}

// Convert a 16-bit value from host byte order to network byte order (big-endian)
uint16_t my_htons(uint16_t hostshort) {
    return (hostshort >> 8) |              // Shift MSB to LSB position
           (hostshort << 8);               // Shift LSB to MSB position
}

// Convert a 32-bit value from network byte order to host byte order
uint32_t my_ntohl(uint32_t netlong) {
    return my_htonl(netlong);               // Network byte order is big-endian, so reverse it using my_htonl
}

// (Not in use right now, probably later)
// Convert a 16-bit value from network byte order to host byte order
uint16_t my_ntohs(uint16_t netshort) {
    return my_htons(netshort);              // Network byte order is big-endian, so reverse it using my_htons
}

// IPv4 support for inet_pton
// Convert an IPv4 address from presentation (string) format to network (binary) format
int my_inet_pton(int af, const char *src, void *dst) {
    if (af == MY_AF_INET) {  // Check if the address family is AF_INET (IPv4)
        struct my_in_addr *addr = (struct my_in_addr *)dst;  // Cast destination to my_in_addr type
        unsigned int a, b, c, d;
        if (sscanf(src, "%u.%u.%u.%u", &a, &b, &c, &d) == 4) {  // Parse the IPv4 address into four integers
            addr->s_addr = my_htonl((a << 24) | (b << 16) | (c << 8) | d); // Pack and convert to network byte order
            return 1;  // Return 1 to indicate success
        }
        my_perror("my_inet_pton - Invalid IPv4 address format");  // Print an error message if the format is invalid
        return 0;  // Return 0 to indicate failure
    }
    my_perror("my_inet_pton - Only AF_INET is supported");  // Print an error message if the address family is not AF_INET
    return -1;  // Return -1 to indicate failure
}

// IPv4 support for inet_ntop
// Convert an IPv4 address from network (binary) format to presentation (string) format
const char *my_inet_ntop(int af, const void *src, char *dst, uint32_t size) {
    if (af == MY_AF_INET) {  // Check if the address family is AF_INET (IPv4)
        const struct my_in_addr *addr = (const struct my_in_addr *)src;  // Cast source to my_in_addr type
        if (size < MY_INET_ADDRSTRLEN) {  // Check if the provided buffer size is sufficient
            my_perror("my_inet_ntop - Insufficient buffer size");  // Print an error message if buffer is too small
            return NULL;  // Return NULL to indicate failure
        }
        snprintf(dst, size, "%u.%u.%u.%u",
                 (my_ntohl(addr->s_addr) >> 24) & 0xFF,  // Extract and format the MSB
                 (my_ntohl(addr->s_addr) >> 16) & 0xFF,  // Extract and format the second byte
                 (my_ntohl(addr->s_addr) >> 8) & 0xFF,   // Extract and format the third byte
                 my_ntohl(addr->s_addr) & 0xFF);         // Extract and format the LSB
        return dst;  // Return the formatted string (IPv4 address in presentation format)
    }
    my_perror("my_inet_ntop - Only AF_INET is supported");  // Print an error message if address family is not AF_INET
    return NULL;  // Return NULL to indicate failure
}