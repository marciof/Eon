#include <stdlib.h>
#include <string.h>
#include "Str.h"

void Str_free(void* str) {
    free(((struct Str*) str)->val);
    free(str);
}

struct Str* Str_from_chars(char* chars, size_t len, struct Err* err) {
    char* val = malloc(len * sizeof(*chars));

    if (val == NULL) {
        return ERR_ADD_ERRNO(err, errno);
    }

    struct Str* str = malloc(sizeof(*str));

    if (str == NULL) {
        int nr = errno;
        free(val);
        return ERR_ADD_ERRNO(err, nr);
    }

    str->val = val;
    str->len = len;
    strncpy(str->val, chars, len);
    return REF_INIT(str, Str_free);
}
