#pragma once
#include "Any.h"
#include "Err.h"
#include "Ref.h"
#include "Str.h"

struct Input {
    union Any arg;
    char* location;
    int (*read)(union Any arg, bool is_peek, bool* has_err); // `EOF` on EOF
    REF_FIELDS;
};

struct Input* Input_from_stdin(bool* has_err);
