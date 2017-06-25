#pragma once
#include <stddef.h>
#include "Err.h"
#include "Ref.h"

struct Str {
    char* val;
    size_t len;
    size_t max_len;
    REF_FIELDS;
};

void Str_append_char(struct Str* str, char ch, bool* has_err);
struct Str* Str_new(bool* has_err);
