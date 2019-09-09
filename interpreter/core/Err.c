#include <string.h>
#include "Err.h"

void k_Err_describe_text(struct k_Err* err, k_Err_log log, intptr_t logger) {
    log(logger, "{s}", (char*) err->arg);
}

bool k_Err_has(struct k_Err* err) {
    return err->describe != NULL;
}

// FIXME: discourage reuse? make it an error?
void k_Err_set(
        struct k_Err* err,
        void (*describe)(struct k_Err*, k_Err_log, intptr_t),
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
