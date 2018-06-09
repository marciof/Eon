#include <string.h>
#include "Err.h"
#include "Log.h"

void k_Err_describe(struct k_Err* err) {
    struct k_Err discard_log_err = K_ERR_INIT;

    // FIXME: pass Log over
    err->describe(err);

    // FIXME: avoid direct use of the singleton
    k_Log_msg(k_Log_get(), &discard_log_err, K_LOG_ERROR,
        "  `{s}()` at {s}:{iu}", err->function, err->file, err->line);
}

void k_Err_describe_text(struct k_Err* err) {
    struct k_Err discard_log_err = K_ERR_INIT;

    k_Log_msg(k_Log_get(), &discard_log_err, K_LOG_ERROR,
        "{s}", (char*) err->arg);
}

bool k_Err_has(struct k_Err* err) {
    return err->describe != NULL;
}

void k_Err_reset(struct k_Err* err) {
    err->describe = NULL;
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
