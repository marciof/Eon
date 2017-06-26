#pragma once
#include "Err.h"
#include "Input.h"
#include "Ref.h"
#include "Str.h"

enum e_Token_Type {
    E_TOKEN_COMMENT,
    E_TOKEN_WHITESPACE,
};

struct e_Token {
    enum e_Token_Type type;
    struct e_Str* str;
    struct e_Input* input;
    size_t line;
    size_t column;
    E_REF_FIELD;
};

// `NULL` on EOF
struct e_Token* e_Token_parse(struct e_Input* input, bool* has_err);
