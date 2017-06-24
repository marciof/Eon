#include <stdlib.h>
#include <string.h>
#include "Str.h"

static void Str_free(void* str) {
    free(((struct Str*) str)->val);
    free(str);
}

void Str_append(struct Str* target, struct Str* source, bool* has_err) {
    size_t target_size = (target->len * sizeof(*target->val));
    size_t source_size = (source->len * sizeof(*source->val));
    char* new_val = realloc(target->val, target_size + source_size);

    if (new_val == NULL) {
        *has_err = true;
        ERR_PRINT_ERRNO();
        return;
    }

    target->val = new_val;
    strncpy(target->val + target->len, source->val, source->len);
}

struct Str* Str_from_chars(char* chars, size_t len, bool* has_err) {
    char* val = malloc(len * sizeof(*chars));

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
    str->len = len;
    strncpy(str->val, chars, len);
    return REF_INIT(str, Str_free);
}
