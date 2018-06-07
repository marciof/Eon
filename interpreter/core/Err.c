#include <string.h>
#include "Err.h"
#include "Log.h"

void k_Err_describe(struct k_Err* err) {
    // FIXME: pass k_Log over
    err->describe(err);

    // FIXME: avoid direct use of the singleton
    k_Log_msg(k_Log_get(), K_LOG_WARN, "  `{s}()` at {s}:{iu}u",
        err->function, err->file, err->line);
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
