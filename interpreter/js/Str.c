#include <stdint.h>
#include <stdlib.h>
#include "Str.h"

static void increase_max_len(struct k_Str* str, struct k_Err* err) {
    if (str->max_len == SIZE_MAX) {
        K_ERR_SET_ERRNO(err, ENOMEM);
        return;
    }

    size_t new_max_len = (size_t) (str->max_len * 1.5);

    if (new_max_len < str->max_len) {
        new_max_len = SIZE_MAX;
    }

    char* new_val = realloc(str->val, new_max_len * sizeof(*str->val));

    if (new_val == NULL) {
        K_ERR_SET_ERRNO(err, errno);
        return;
    }

    str->val = new_val;
    str->max_len = new_max_len;
}

static void free_str(void* str) {
    free(((struct k_Str*) str)->val);
    free(str);
}

void k_Str_add_char(struct k_Str* str, char ch, struct k_Err* err) {
    if (str->len == str->max_len) {
        increase_max_len(str, err);

        if (k_Err_has(err)) {
            return;
        }
    }

    str->val[str->len++] = ch;
}

struct k_Str* k_Str_new(struct k_Err* err) {
    size_t max_len = 32;
    char* val = malloc(max_len * sizeof(*val));

    if (val == NULL) {
        K_ERR_SET_ERRNO(err, errno);
        return NULL;
    }

    struct k_Str* str = malloc(sizeof(*str));

    if (str == NULL) {
        K_ERR_SET_ERRNO(err, errno);
        free(val);
        return NULL;
    }

    str->val = val;
    str->len = 0;
    str->max_len = max_len;
    return K_REF_INIT(str, free_str);
}
