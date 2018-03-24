#include <string.h>
#include "Err.h"

void k_Err_describe(struct k_Err* err, FILE* output) {
    err->describe(err, output);
    fprintf(output, "  `%s()` at %s:%zu\n",
        err->function, err->file, err->line);
}

void k_Err_describe_errno(struct k_Err* err, FILE* output) {
    int num = (int) err->arg;
    fprintf(output, "%s (errno 0x%X)\n", strerror(num), num);
}

bool k_Err_has(struct k_Err* err) {
    return err->describe != NULL;
}

void k_Err_set(
        struct k_Err* err,
        void (* describe)(struct k_Err*, FILE*),
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
