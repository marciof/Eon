#include <string.h>
#include "Err.h"

void k_Err_describe_text(struct k_Err* err, k_Err_log log) {
    log("{s}", (char*) err->arg);
}

bool k_Err_has(struct k_Err* err) {
    return err->describe != NULL;
}

void k_Err_reset(struct k_Err* err) {
    err->describe = NULL;
    err->arg = 0;
}

void k_Err_set(
        struct k_Err* err,
        void (*describe)(struct k_Err*, k_Err_log),
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
