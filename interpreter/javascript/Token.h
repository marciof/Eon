#pragma once
#include "Err.h"
#include "Input.h"
#include "Ref.h"
#include "Str.h"

enum Token_Type {
    COMMENT,
    WHITE_SPACE,
};

struct Token {
    enum Token_Type type;
    struct Str* str;
    REF_FIELDS;
};

struct Token* Token_read(struct Input* input, bool* has_err);
