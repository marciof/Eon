#pragma once
#include <stdbool.h>
#include <stddef.h>
#include "Any.h"
#include "Err.h"
#include "Ref.h"
#include "Str.h"

#define COMMENT_QUOTE 0x23
#define END_OF_LINE 0xA
#define SPACE 0x20

struct Input {
    union Any arg;
    char* location;
    size_t line;
    size_t column;
    int (*read)(struct Input* input, bool is_peek, bool* has_err); // `EOF`
    REF_FIELDS;
};

struct Input* Input_from_stdin(bool* has_err);
