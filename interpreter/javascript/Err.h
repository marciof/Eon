#pragma once
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// FIXME: decouple detecting an error from printing

#define K_ERR_LOCATION() \
    fprintf(stderr, "    `%s()` at %s:%d\n", __func__, __FILE__, __LINE__)

#define K_ERR_ERRNO() \
    fprintf(stderr, "%s (errno 0x%X)\n", strerror(errno), errno); \
    K_ERR_LOCATION()

#define K_ERR_PRINTF(format, ...) \
    fprintf(stderr, (format), __VA_ARGS__); \
    fprintf(stderr, "\n"); \
    K_ERR_LOCATION()
