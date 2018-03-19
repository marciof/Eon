#pragma once
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "Err.h"
#include "Ref.h"
#include "Str.h"

#define E_COMMENT_QUOTE 0x23
#define E_END_OF_LINE 0xA
#define E_SPACE 0x20

struct e_Input {
    E_REF_FIELD;
    // `EOF` on EOF
    int (*read_ch)(struct e_Input* input, bool* has_err);
    int (*peek_ch)(struct e_Input* input, bool* has_err);
    char* location;
    size_t line;
    size_t column;
    uint8_t val[];
};

struct e_Input* e_Input_from_fd(int fd, char* location, bool* has_err);
