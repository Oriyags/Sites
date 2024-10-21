#include "socket_utils.h"

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

// Byte Order Functions
// Convert a 32-bit value from host byte order to network byte order (big-endian)
uint32_t my_htonl(uint32_t hostlong) {
    return ((hostlong & 0xff) << 24) |    // Move least significant byte (LSB) to the most significant position
           ((hostlong & 0xff00) << 8) |   // Move second byte from LSB to its proper position
           ((hostlong & 0xff0000) >> 8) | // Move third byte from LSB to its proper position
           ((hostlong & 0xff000000) >> 24); // Move most significant byte (MSB) to the least significant position
}

// Convert a 16-bit value from host byte order to network byte order
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