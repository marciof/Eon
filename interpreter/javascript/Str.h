#pragma once
#include <stddef.h>
#include "Err.h"
#include "Ref.h"

struct Str {
    char* val;
    size_t len;
    REF_FIELDS;
};

void Str_append(struct Str* target, struct Str* source, bool* has_err);
void Str_free(void* str);
struct Str* Str_from_chars(char* chars, size_t len, bool* has_err);
