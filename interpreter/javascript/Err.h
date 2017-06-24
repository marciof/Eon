#pragma once
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define ERR_PRINT_LOCATION() \
    fprintf(stderr, "\t%s() at %s:%d\n", __func__, __FILE__, __LINE__)

#define ERR_PRINT_ERRNO() \
    fprintf(stderr, "%s (errno 0x%X)\n", strerror(errno), errno); \
    ERR_PRINT_LOCATION()

#define ERR_PRINT(msg) \
    fprintf(stderr, "%s\n", (msg)); \
    ERR_PRINT_LOCATION()

#define ERR_PRINTF(format, ...) \
    fprintf(stderr, (format), __VA_ARGS__); \
    fprintf(stderr, "\n"); \
    ERR_PRINT_LOCATION()
