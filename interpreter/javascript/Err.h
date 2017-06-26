#pragma once
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// FIXME: decouple detecting an error from printing

#define E_ERR_LOCATION() \
    fprintf(stderr, "    `%s()` at %s:%d\n", __func__, __FILE__, __LINE__)

#define E_ERR_ERRNO() \
    fprintf(stderr, "%s (errno 0x%X)\n", strerror(errno), errno); \
    E_ERR_LOCATION()

#define E_ERR_PRINTF(format, ...) \
    fprintf(stderr, (format), __VA_ARGS__); \
    fprintf(stderr, "\n"); \
    E_ERR_LOCATION()
