#ifndef SOCKEET_UTILS_H
#define SOCKEET_UTILS_H

#include "sockets_lib.h"
#include "syscall_wrappers.h"
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>         


void my_perror(const char *s);
uint32_t my_htonl(uint32_t hostlong);
uint16_t my_htons(uint16_t hostshort);
uint32_t my_ntohl(uint32_t netlong);
uint16_t my_ntohs(uint16_t netshort);

int my_inet_pton(int af, const char *src, void *dst);
const char *my_inet_ntop(int af, const void *src, char *dst, uint32_t size);

#endif