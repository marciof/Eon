#pragma once
#include <stddef.h>
#include "Err.h"
#include "ref.h"

struct e_Str {
    char* val;
    size_t len;
    size_t max_len;
    E_REF_FIELDS;
};

void e_Str_add_char(struct e_Str* str, char ch, bool* has_err);
struct e_Str* e_Str_new(bool* has_err);
