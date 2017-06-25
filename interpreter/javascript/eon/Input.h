#pragma once
#include <stdbool.h>
#include <stddef.h>
#include "Any.h"
#include "Err.h"
#include "Ref.h"
#include "Str.h"

#define E_COMMENT_QUOTE 0x23
#define E_END_OF_LINE 0xA
#define E_SPACE 0x20

struct e_Input {
    union e_Any arg;
    char* location;
    size_t line;
    size_t col;
    // `EOF` on EOF
    int (*read)(struct e_Input* input, bool is_peek, bool* has_err);
    E_REF_FIELDS;
};

struct e_Input* e_Input_from_fd(int fd, char* location, bool* has_err);
