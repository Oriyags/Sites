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