#pragma once
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "../core/Err.h"
#include "../core/Ref.h"
#include "Str.h"

#define K_COMMENT_QUOTE 0x23
#define K_END_OF_LINE 0xA
#define K_SPACE 0x20

struct k_Input {
    K_REF_FIELD;
    /**
     * `EOF` on EOF
     */
    int (*read_ch)(struct k_Input* input, struct k_Err* err);
    int (*peek_ch)(struct k_Input* input, struct k_Err* err);
    char* location;
    size_t line;
    size_t column;
    uint8_t val[];
};

struct k_Input* k_Input_from_fd(int fd, char* location, struct k_Err* err);
