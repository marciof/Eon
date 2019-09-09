#include <stdio.h>
#include "../core/Bit.h"
#include "../core/Log.h"

// FIXME: add colors
static FILE* get_stream(enum k_Log_Level lvl) {
    return ((lvl == K_LOG_LEVEL_ERROR) || (lvl == K_LOG_LEVEL_WARN))
        ? stderr
        : stdout;
}

// FIXME: error handling fputc
static void print_ch(
        K_BIT_UNUSED(struct k_Log* log),
        enum k_Log_Level lvl,
        char ch,
        K_BIT_UNUSED(struct k_Err* err)) {

    fputc(ch, get_stream(lvl));
}

// FIXME: error handling fputs
static void print_str(
        K_BIT_UNUSED(struct k_Log* log),
        enum k_Log_Level lvl,
        char* str,
        K_BIT_UNUSED(struct k_Err* err)) {

    fputs(str, get_stream(lvl));
}

void k_Std_Stream_Log_init(struct k_Log* log) {
    log->print_ch = print_ch;
    log->print_str = print_str;
}
