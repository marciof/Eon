#include <stdio.h>
#include "../core/Bit.h"
#include "../core/std/Time.h"
#include "Errno.h"
#include "Log.h"

static FILE* get_stream(enum k_Log_Level lvl) {
    return ((lvl == K_LOG_LEVEL_ERROR) || (lvl == K_LOG_LEVEL_WARN))
        ? stderr
        : stdout;
}

static void print_ch(
        K_BIT_UNUSED(struct k_Log* log),
        enum k_Log_Level lvl,
        char ch,
        struct k_Err* err) {

    if (fputc(ch, get_stream(lvl)) == EOF) {
        K_ERR_SET_ERRNO(err, errno);
    }
}

static void print_str(
        K_BIT_UNUSED(struct k_Log* log),
        enum k_Log_Level lvl,
        char* str,
        struct k_Err* err) {

    if (fputs(str, get_stream(lvl)) == EOF) {
        K_ERR_SET_ERRNO(err, errno);
    }
}

static void print_timestamp(
        K_BIT_UNUSED(struct k_Log* log),
        enum k_Log_Level lvl,
        struct k_Err* err) {

    time_t stamp = time(NULL);

    if (stamp == -1) {
        K_ERR_SET_ERRNO(err, errno);
        return;
    }

    struct tm utc;

    if (gmtime_r(&stamp, &utc) == NULL) {
        K_ERR_SET_ERRNO(err, errno);
        return;
    }

    int len = fprintf(get_stream(lvl),
        "%04u-%02u-%02uT%02u:%02u:%02uZ",
        utc.tm_year + 1900, utc.tm_mon + 1, utc.tm_mday,
        utc.tm_hour, utc.tm_min, utc.tm_sec);

    if (len < 0) {
        K_ERR_SET_ERRNO(err, errno);
    }
}

void k_Std_Stream_Log_init(struct k_Log* log) {
    log->print_ch = print_ch;
    log->print_str = print_str;
    log->print_timestamp = print_timestamp;
}
