#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "str.h"

static void str_increase_max_len(struct eon_str* str, bool* has_err) {
    if (str->max_len == SIZE_MAX) {
        *has_err = true;
        errno = ENOMEM;
        EON_ERR_ERRNO();
        return;
    }

    size_t new_max_len = (size_t) (str->max_len * 1.5);

    if (new_max_len < str->max_len) {
        new_max_len = SIZE_MAX;
    }

    char* new_val = realloc(str->val, new_max_len * sizeof(*str->val));

    if (new_val == NULL) {
        *has_err = true;
        EON_ERR_ERRNO();
        return;
    }

    str->val = new_val;
    str->max_len = new_max_len;
}

static void str_free(void* str) {
    free(((struct eon_str*) str)->val);
    free(str);
}

void eon_str_add_char(struct eon_str* str, char ch, bool* has_err) {
    if (str->len == str->max_len) {
        str_increase_max_len(str, has_err);

        if (*has_err) {
            return;
        }
    }

    str->val[str->len++] = ch;
}

struct eon_str* eon_str_new(bool* has_err) {
    size_t max_len = 32;
    char* val = malloc(max_len * sizeof(*val));

    if (val == NULL) {
        *has_err = true;
        EON_ERR_ERRNO();
        return NULL;
    }

    struct eon_str* str = malloc(sizeof(*str));

    if (str == NULL) {
        *has_err = true;
        EON_ERR_ERRNO();
        free(val);
        return NULL;
    }

    str->val = val;
    str->len = 0;
    str->max_len = max_len;
    return EON_REF_INIT(str, str_free);
}
