#pragma once
#include <stddef.h>
#include "err.h"
#include "ref.h"

struct eon_str {
    char* val;
    size_t len;
    size_t max_len;
    EON_REF_FIELDS;
};

void eon_str_add_char(struct eon_str* str, char ch, bool* has_err);
struct eon_str* eon_str_new(bool* has_err);
