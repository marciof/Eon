#pragma once
#include "err.h"
#include "input.h"
#include "ref.h"
#include "str.h"

enum eon_token_type {
    EON_TOKEN_COMMENT,
    EON_TOKEN_WHITESPACE,
};

struct eon_token {
    enum eon_token_type type;
    struct eon_str* str;
    struct eon_input* input;
    size_t line;
    size_t col;
    EON_REF_FIELDS;
};

// `NULL` on EOF
struct eon_token* eon_token_parse(struct eon_input* input, bool* has_err);
