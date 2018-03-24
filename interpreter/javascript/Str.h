#pragma once
#include <stddef.h>
#include "Err.h"
#include "Ref.h"

struct k_Str {
    K_REF_FIELD;
    char* val;
    size_t len;
    size_t max_len;
};

void k_Str_add_char(struct k_Str* str, char ch, struct k_Err* err);
struct k_Str* k_Str_new(struct k_Err* err);
