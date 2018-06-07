#pragma once
#include "../core/Ref.h"
#include "Errno.h"
#include "Input.h"
#include "Str.h"

enum k_Token_Type {
    K_TOKEN_COMMENT,
    K_TOKEN_WHITESPACE,
};

struct k_Token {
    K_REF_FIELD;
    enum k_Token_Type type;
    struct k_Str* str;
    struct k_Input* input;
    size_t line;
    size_t column;
};

/** @return `NULL` on EOF */
struct k_Token* k_Token_parse(struct k_Input* input, struct k_Err* err);
