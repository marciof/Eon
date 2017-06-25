#pragma once
#include "Err.h"
#include "Input.h"
#include "Ref.h"
#include "Str.h"

enum Token_Type {
    TOKEN_COMMENT,
    TOKEN_WHITESPACE,
};

struct Token {
    enum Token_Type type;
    struct Str* str;
    REF_FIELDS;
};

struct Token* Token_read(struct Input* input, bool* has_err); // `NULL` on EOF
