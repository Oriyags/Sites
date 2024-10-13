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

// Define necessary constants and structures
#define AF_INET 2
#define SOCK_STREAM 1    // Type for TCP
#define SOCK_DGRAM 2     // Type for UDP
#define INET_ADDRSTRLEN 16

// Inline function to make a syscall for socket
inline int sys_socket(int domain, int type, int protocol) {
    return syscall(__NR_socket, domain, type, protocol);
}

// Create a socket with the specified domain, type, and protocol
int my_socket(int domain, int type, int protocol) {
    if (domain != AF_INET) {  // Check if the domain is AF_INET
        my_perror("my_socket - Only AF_INET is supported");  // Print an error message
        return -1;  // Return -1 to indicate failure
    }
    int sockfd = sys_socket(domain, type, protocol);  // Use the inline function to create the socket
    if (sockfd < 0) {
        my_perror("my_socket");  // Print an error message if socket creation fails
    }
    return sockfd;  // Return the socket file descriptor
}

// Inline function to make a syscall for bind
inline int sys_bind(int sockfd, const struct my_sockaddr *addr, uint32_t addrlen) {
    return syscall(__NR_bind, sockfd, addr, addrlen);
}

// Bind a socket to a specific address and port
int my_bind(int sockfd, const struct my_sockaddr *addr, uint32_t addrlen) {
    int result = sys_bind(sockfd, (const struct my_sockaddr *)addr, addrlen);  // Call the syscall to bind the socket
    if (result < 0) {
        my_perror("my_bind");  // Print an error message if bind fails
    }
    return result;  // Return the result of the bind operation
}

// Inline function to make a syscall for listen
inline int sys_listen(int sockfd, int backlog) {
    return syscall(__NR_listen, sockfd, backlog);
}

// Listen for incoming connections on a socket
int my_listen(int sockfd, int backlog) {
    int result = sys_listen(sockfd, backlog);           // Call the syscall to listen on the socket
    if (result < 0) {
        my_perror("my_listen");  // Print an error message if listen fails
    }
    return result;  // Return the result of the listen operation
}

// Inline function to make a syscall for accept
inline int sys_accept(int sockfd, void *addr, uint32_t *addrlen) {
    return syscall(__NR_accept, sockfd, addr, addrlen);
}

// Accept an incoming connection on a socket
int my_accept(int sockfd, void *addr, uint32_t *addrlen) {
    int new_sockfd = sys_accept(sockfd, addr, addrlen); // Call the syscall to accept a connection
    if (new_sockfd < 0) {
        my_perror("my_accept");  // Print an error message if accept fails
    }
    return new_sockfd;  // Return the new socket file descriptor for the accepted connection
}

// Inline function to make a syscall for connect
inline int sys_connect(int sockfd, const *addr, uint32_t *addrlen) {
    return syscall(__NR_connect, sockfd, addr, addrlen);
}

// Connect to a remote address using a socket
int my_connect(int sockfd, const void *addr, uint32_t addrlen) {
    int result = sys_connect(sockfd, addr, addrlen);    // Call the syscall to connect the socket
    if (result < 0) {
        my_perror("my_connect");                                  // Print an error message if connect fails
    }
    return result;  // Return the result of the connect operation
}

// Inline function to make a syscall for close
inline int sys_close(int sockfd) {
    return syscall(__NR_connect, sockfd);
}

// Close a socket
int my_close(int sockfd) {
    int result = sys_close(sockfd);         // Call the syscall to close the socket
    if (result < 0) {
        my_perror("my_close");              // Print an error message if close fails
    }
    return result;
}

// Inline function to make a syscall for send
inline ssize_t sys_send(int sockfd, const void *buf, size_t len, int flags) {
    return syscall(__NR_sendto, sockfd, buf, len, flags, NULL, 0);
}

// Data Transmission Functions
// Send data on a socket
ssize_t my_send(int sockfd, const void *buf, size_t len, int flags) {
    ssize_t result = sys_send(sockfd, buf, len, flags);
    if (result < 0) {
        my_perror("my_send");  // Print an error message if send fails
    }
    return result;  // Return the number of bytes sent
}

// Receive data from a socket
ssize_t my_recv(int sockfd, void *buf, size_t len, int flags) {
    ssize_t result = syscall(__NR_recvfrom, sockfd, buf, len, flags, NULL, NULL);
    if (result < 0) {
        my_perror("my_recv");  // Print an error message if receive fails
    }
    return result;
}

// Send data to a specific address using a socket
ssize_t my_sendto(int sockfd, const void *buf, size_t len, int flags, const void *dest_addr, uint32_t addrlen) {
    ssize_t result = syscall(__NR_sendto, sockfd, buf, len, flags, dest_addr, addrlen);
    if (result < 0) {
        my_perror("my_sendto");  // Print an error message if sendto fails
    }
    return result;  // Return the number of bytes sent
}

// Receive data from a specific address using a socket
ssize_t my_recvfrom(int sockfd, void *buf, size_t len, int flags, void *src_addr, uint32_t *addrlen) {
    ssize_t result = syscall(__NR_recvfrom, sockfd, buf, len, flags, src_addr, addrlen); 
    if (result < 0) {
        my_perror("my_recvfrom");  // Print an error message if recvfrom fails
    }
    return result;
}

// Helper function to print errors
// It prints an error message to STDERR with a description
void my_perror(const char *s) {
    if (s && *s) { 
        write(STDERR_FILENO, s, strlen(s));                       // Print the error message prefix
        write(STDERR_FILENO, ": ", 2);                            // Print ": " after the prefix
    } 
    const char *error_message = strerror(errno);                  // Get the error message based on errno
    write(STDERR_FILENO, error_message, strlen(error_message));   // Print the error message
    write(STDERR_FILENO, "\n", 1);  // Print a newline character
}

// Memory Functions
// Set a block of memory to a specific value
void *my_memset(void *s, int c, size_t n) {
    unsigned char *p = s;  // Cast the pointer to unsigned char*
    while (n--) {          // Loop through the number of bytes
        *p++ = (unsigned char)c; // Set each byte to the value c
    }
    return s;  // Return the pointer to the memory block
}

// Byte Order Functions
// Convert a 32-bit value from host byte order to network byte order (big-endian)
uint32_t my_htonl(uint32_t hostlong) {
    return ((hostlong & 0xff) << 24) |
           ((hostlong & 0xff00) << 8) |
           ((hostlong & 0xff0000) >> 8) |
           ((hostlong & 0xff000000) >> 24);
}

// Convert a 16-bit value from host byte order to network byte order (big-endian)
uint16_t my_htons(uint16_t hostshort) {
    return (hostshort >> 8) | (hostshort << 8);
}

// Convert a 32-bit value from network byte order to host byte order
uint32_t my_ntohl(uint32_t netlong) {
    return my_htonl(netlong);               // Network byte order is big-endian
}

// Convert a 16-bit value from network byte order to host byte order
uint16_t my_ntohs(uint16_t netshort) {
    return my_htons(netshort);  // Network byte order is big-endian
}

// IPv4 support for inet_pton
// Convert an IPv4 address from presentation format to network format
int my_inet_pton(int af, const char *src, void *dst) {
    if (af == AF_INET) {  // Check if the address family is AF_INET
        struct my_in_addr *addr = (struct my_in_addr *)dst;  // Cast destination to my_in_addr
        unsigned int a, b, c, d;
        if (sscanf(src, "%u.%u.%u.%u", &a, &b, &c, &d) == 4) {  // Parse the IPv4 address
            addr->s_addr = my_htonl((a << 24) | (b << 16) | (c << 8) | d); // Convert to network format
            return 1;  // Return 1 to indicate success
        }
        my_perror("my_inet_pton - Invalid IPv4 address format");  // Print an error message if the format is invalid
        return 0;  // Return 0 to indicate failure
    }
    my_perror("my_inet_pton - Only AF_INET is supported");  // Print an error message if address family is not AF_INET
    return -1;  // Return -1 to indicate failure
}

// IPv4 support for inet_ntop
// Convert an IPv4 address from network format to presentation format
const char *my_inet_ntop(int af, const void *src, char *dst, uint32_t size) {
    if (af == AF_INET) {  // Check if the address family is AF_INET
        const struct my_in_addr *addr = (const struct my_in_addr *)src;  // Cast source to my_in_addr
        if (size < INET_ADDRSTRLEN) {  // Check if the buffer size is sufficient
            my_perror("my_inet_ntop - Insufficient buffer size");  // Print an error message if the buffer is too small
            return NULL;  // Return NULL to indicate failure
        }
        snprintf(dst, size, "%u.%u.%u.%u",
                 (my_ntohl(addr->s_addr) >> 24) & 0xFF,
                 (my_ntohl(addr->s_addr) >> 16) & 0xFF,
                 (my_ntohl(addr->s_addr) >> 8) & 0xFF,
                 my_ntohl(addr->s_addr) & 0xFF);  // Format the address as a string
        return dst;  // Return the address string
    }
    my_perror("my_inet_ntop - Only AF_INET is supported");  // Print an error message if address family is not AF_INET
    return NULL;  // Return NULL to indicate failure
}

// Socket Option Management
// Set socket options
int my_setsockopt(int sockfd, int level, int optname, const void *optval, uint32_t optlen) {
    int result = syscall(__NR_setsockopt, sockfd, level, optname, optval, optlen);  // Call the syscall to set socket options
    if (result < 0) {
        my_perror("my_setsockopt");  // Print an error message if setsockopt fails
    }
    return result;  // Return the result of the setsockopt operation
}

// Get socket options
int my_getsockopt(int sockfd, int level, int optname, void *optval, uint32_t *optlen) {
    int result = syscall(__NR_getsockopt, sockfd, level, optname, optval, optlen);  // Call the syscall to get socket options
    if (result < 0) {
        my_perror("my_getsockopt");  // Print an error message if getsockopt fails
    }
    return result;  // Return the result of the getsockopt operation
}

// Control non-blocking mode using fcntl (file control)
// Set or get file descriptor flags
int my_fcntl(int sockfd, int cmd, long arg) {
    int result = syscall(__NR_fcntl, sockfd, cmd, arg);  // Call the syscall to control file descriptor
    if (result < 0) {
        my_perror("my_fcntl");  // Print an error message if fcntl fails
    }
    return result;  // Return the result of the fcntl operation
}