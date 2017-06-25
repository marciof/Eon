#pragma once
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define EON_ERR_LOCATION() \
    fprintf(stderr, "    `%s()` at %s:%d\n", __func__, __FILE__, __LINE__)

#define EON_ERR_ERRNO() \
    fprintf(stderr, "%s (errno 0x%X)\n", strerror(errno), errno); \
    EON_ERR_LOCATION()

#define EON_ERR_PRINTF(format, ...) \
    fprintf(stderr, (format), __VA_ARGS__); \
    fprintf(stderr, "\n"); \
    EON_ERR_LOCATION()
