#pragma once
#include "Err.h"
#include "Input.h"
#include "Ref.h"
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

// `NULL` on EOF
struct k_Token* k_Token_parse(struct k_Input* input, bool* has_err);
