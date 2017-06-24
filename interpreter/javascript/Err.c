#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "Err.h"

void* Err_add(
        struct Err* err,
        union Any arg,
        const char* function,
        const char* file,
        size_t line,
        char* (*describe)(union Any)) {

    for (ssize_t i = ERR_STACK_LEN - 1 - 1; i >= 0; --i) {
        err->stack[i + 1] = err->stack[i];
    }

    struct Err_Item* err_item = &err->stack[0];

    err_item->arg = arg;
    err_item->function = function;
    err_item->file = file;
    err_item->line = line;
    err_item->describe = describe;

    return NULL;
}

char* Err_describe_errno(union Any arg) {
    return strerror((int) arg.val);
}

char* Err_describe_cstring(union Any arg) {
    return arg.ptr;
}

void Err_print(struct Err* err, FILE* stream) {
    if (!ERR_HAS(err)) {
        return;
    }

    for (size_t i = 0; i < ERR_STACK_LEN; ++i) {
        struct Err_Item* err_item = &err->stack[i];

        if (err_item->describe == NULL) {
            break;
        }

        int result = fprintf(stream, "%s\n\t%s() at %s:%zu\n",
            err_item->describe(err_item->arg),
            err_item->function,
            err_item->file,
            err_item->line);

        if (result < 0) {
            abort();
        }
    }
}
