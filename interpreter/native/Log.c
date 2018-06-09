#include <stdio.h>
#include "../core/Bit.h"
#include "../core/Log.h"

struct Native_Log {
    FILE* stream;
};

// FIXME: add colors
static void prepare(
        struct k_Log* log,
        K_BIT_UNUSED(struct k_Err* err),
        enum k_Log_Level lvl) {

    struct Native_Log* native_log = (struct Native_Log*) log->val;

    // FIXME: find an alternative to mutating this every time
    native_log->stream = (lvl == K_LOG_ERROR) || (lvl == K_LOG_WARN)
        ? stderr
        : stdout;
}

// FIXME: error handling fputc
static void print_ch(
        struct k_Log* log,
        K_BIT_UNUSED(struct k_Err* err),
        char ch) {

    fputc(ch, ((struct Native_Log*) log->val)->stream);
}

// FIXME: error handling fputs
static void print_str(
        struct k_Log* log,
        K_BIT_UNUSED(struct k_Err* err),
        const char* str) {

    fputs(str, ((struct Native_Log*) log->val)->stream);
}

struct k_Log* k_Log_get(void) {
    static uint8_t data_area[sizeof(struct k_Log) + sizeof(struct Native_Log)];
    static struct k_Log* log = NULL;

    if (log == NULL) {
        log = (struct k_Log*) data_area;
        log->prepare = prepare;
        log->print_ch = print_ch;
        log->print_str = print_str;
        ((struct Native_Log*) log->val)->stream = stdout;
    }

    return log;
}
