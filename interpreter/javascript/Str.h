#pragma once
#include <stddef.h>
#include "Err.h"
#include "Ref.h"

struct e_Str {
    E_REF_FIELD;
    char* val;
    size_t len;
    size_t max_len;
};

void e_Str_add_char(struct e_Str* str, char ch, bool* has_err);
struct e_Str* e_Str_new(bool* has_err);
