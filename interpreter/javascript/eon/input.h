#pragma once
#include <stdbool.h>
#include <stddef.h>
#include "any.h"
#include "err.h"
#include "ref.h"
#include "str.h"

#define EON_COMMENT_QUOTE 0x23
#define EON_END_OF_LINE 0xA
#define EON_SPACE 0x20

struct eon_input {
    union eon_any arg;
    char* location;
    size_t line;
    size_t col;
    int (*read)(struct eon_input* input, bool is_peek, bool* has_err); // `EOF`
    EON_REF_FIELDS;
};

struct eon_input* eon_input_from_fd(int fd, char* location, bool* has_err);
