#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "Str.h"

static void Str_increase_max_len(struct Str* str, bool* has_err) {
    if (str->max_len == SIZE_MAX) {
        *has_err = true;
        errno = ENOMEM;
        ERR_PRINT_ERRNO();
        return;
    }

    size_t new_max_len = (size_t) (str->max_len * 1.5);

    if (new_max_len < str->max_len) {
        new_max_len = SIZE_MAX;
    }

    char* new_val = realloc(str->val, new_max_len * sizeof(*str->val));

    if (new_val == NULL) {
        *has_err = true;
        ERR_PRINT_ERRNO();
        return;
    }

    str->val = new_val;
    str->max_len = new_max_len;
}

static void Str_free(void* str) {
    free(((struct Str*) str)->val);
    free(str);
}

void Str_append_char(struct Str* str, char ch, bool* has_err) {
    if (str->len == str->max_len) {
        Str_increase_max_len(str, has_err);

        if (*has_err) {
            return;
        }
    }

    str->val[str->len++] = ch;
}

struct Str* Str_new(bool* has_err) {
    size_t max_len = 32;
    char* val = malloc(max_len * sizeof(*val));

    if (val == NULL) {
        *has_err = true;
        ERR_PRINT_ERRNO();
        return NULL;
    }

    struct Str* str = malloc(sizeof(*str));

    if (str == NULL) {
        *has_err = true;
        ERR_PRINT_ERRNO();
        free(val);
        return NULL;
    }

    str->val = val;
    str->len = 0;
    str->max_len = max_len;
    return REF_INIT(str, Str_free);
}
