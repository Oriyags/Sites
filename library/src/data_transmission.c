#include "data_transmission.h"
#include "sockets_lib.h"
#include <sys/syscall.h>

// Send data over a TCP socket
ssize_t my_send(int sockfd, const void *buf, size_t len, int flags) {
    ssize_t result = syscall(__NR_sendto, sockfd, buf, len, flags, NULL, 0);  // Send data using sys_sendto
    if (result < 0) {
        my_perror("my_send");  // Print error message if send fails
    }
    return result;  // Return number of bytes sent
}

// Receive data from a TCP socket
ssize_t my_recv(int sockfd, void *buf, size_t len, int flags) {
    ssize_t result = syscall(__NR_recvfrom, sockfd, buf, len, flags, NULL, NULL);  // Receive data using sys_recvfrom
    if (result < 0) {
        my_perror("my_recv");  // Print error message if recv fails
    }
    return result;  // Return number of bytes received
}

// Send data to a specific address using a socket
ssize_t my_sendto(int sockfd, const void *buf, size_t len, int flags, const struct my_sockaddr *dest_addr, socklen_t addrlen) {
    ssize_t result = sys_sendto(sockfd, buf, len, flags, dest_addr, addrlen);   // Call syscall to send data
    if (result < 0) {
        my_perror("my_sendto");  // Print error message if sendto fails
    }
    return result;  // Return number of bytes sent
}

// Receive data from a specific address using a socket
ssize_t my_recvfrom(int sockfd, void *buf, size_t len, int flags, struct my_sockaddr *src_addr, socklen_t *addrlen) {
    ssize_t result = sys_recvfrom(sockfd, buf, len, flags, src_addr, addrlen);   // Call syscall to receive data
    if (result < 0) {
        my_perror("my_recvfrom");  // Print error message if recvfrom fails
    }
    return result;  // Return number of bytes received
}