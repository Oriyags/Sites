#include "memory_management.h"

// Set a block of memory to a specific value
void *my_memset(void *s, int c, size_t n) {
    unsigned char *p = s;  // Cast pointer to unsigned char for byte-wise operations
    while (n--) {
        *p++ = (unsigned char)c;  // Set each byte in the block to the specified value
    }
    return s;  // Return the pointer to the memory block
}
