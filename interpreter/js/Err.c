#include <stdio.h>
#include <string.h>
#include "Err.h"

void k_Err_describe(struct k_Err* err) {
    err->describe(err);
    fprintf(stderr, "  `%s()` at %s:%zu\n",
        err->function, err->file, err->line);
}

void k_Err_describe_errno(struct k_Err* err) {
    int num = (int) err->arg;
    fprintf(stderr, "%s (errno 0x%X)\n", strerror(num), num);
}

bool k_Err_has(struct k_Err* err) {
    return err->describe != NULL;
}

void k_Err_set(
        struct k_Err* err,
        void (*describe)(struct k_Err*),
        const char* function,
        char* file,
        size_t line,
        intptr_t arg) {

    err->describe = describe;
    err->function = function;
    err->file = file;
    err->line = line;
    err->arg = arg;
}
