#include <stddef.h>
#include <sys/types.h>
#include "Log.h"

#define NUMERIC_BASE_CONVERSION_SYMBOLS "0123456789ABCDEF"
#define PLACEHOLDER_BEGIN '{'
#define PLACEHOLDER_END '}'
#define FORMAT_STR_ERROR "Invalid logging format string"
#define STATIC_ARRAY_LEN(array) (sizeof((array)) / sizeof((array)[0]))

static char* print_int(
        struct k_Log* log,
        struct k_Err* err,
        enum k_Log_Level lvl,
        char* format,
        int integer) {

    if (*format == 'u') {
        ++format;
    }
    else if (integer < 0) {
        log->print_ch(log, lvl, '-', err);
        if (k_Err_has(err)) {
            return NULL;
        }
        integer = -integer;
    }

    switch (*format++) {
        case 'b':
            k_Log_print_unsigned_int(log, err, lvl, (unsigned) integer, 2);
            if (k_Err_has(err)) {
                return NULL;
            }
            log->print_ch(log, lvl, 'b', err);
            break;
        case 'h':
            k_Log_print_unsigned_int(log, err, lvl, (unsigned) integer, 16);
            if (k_Err_has(err)) {
                return NULL;
            }
            log->print_ch(log, lvl, 'h', err);
            break;
        default:
            k_Log_print_unsigned_int(log, err, lvl, (unsigned) integer, 10);
            --format;
            break;
    }

    return format;
}

static void print(
        struct k_Log* log,
        struct k_Err* err,
        enum k_Log_Level lvl,
        char* format,
        va_list args) {

    for (; *format != '\0'; ++format) {
        if (*format == PLACEHOLDER_END) {
            ++format;

            if (*format == PLACEHOLDER_END) {
                log->print_ch(log, lvl, PLACEHOLDER_END, err);
                if (k_Err_has(err)) {
                    return;
                }
                continue;
            }
            else {
                log->print_ch(log, lvl, '\n', err);
                K_ERR_SET_TEXT(err, FORMAT_STR_ERROR);
                return;
            }
        }
        else if (*format != PLACEHOLDER_BEGIN) {
            log->print_ch(log, lvl, *format, err);
            if (k_Err_has(err)) {
                return;
            }
            continue;
        }

        ++format;

        if (*format == PLACEHOLDER_BEGIN) {
            log->print_ch(log, lvl, PLACEHOLDER_BEGIN, err);
            if (k_Err_has(err)) {
                return;
            }
            continue;
        }

        char* str;

        switch (*format++) {
        case 'c':
            log->print_ch(log, lvl, (char) va_arg(args, int), err);
            break;
        case 's':
            str = va_arg(args, char*);
            log->print_str(log, lvl, str == NULL ? "(null)" : str, err);
            break;
        case 'i':
            format = print_int(log, err, lvl, format, va_arg(args, int));
            break;
        default:
            log->print_ch(log, lvl, '\n', err);
            K_ERR_SET_TEXT(err, FORMAT_STR_ERROR);
            break;
        }

        if (k_Err_has(err)) {
            return;
        }
        if (*format != PLACEHOLDER_END) {
            log->print_ch(log, lvl, '\n', err);
            K_ERR_SET_TEXT(err, FORMAT_STR_ERROR);
            return;
        }
    }
}

void print_log(
        struct k_Log* log,
        struct k_Err* err,
        enum k_Log_Level lvl,
        char* format,
        va_list args) {

    char* msg_prefix = (lvl == K_LOG_LEVEL_ERROR) ? " [ERROR] "
        : (lvl == K_LOG_LEVEL_WARN) ? " [WARN] "
        : " [INFO] ";

    log->print_timestamp(log, lvl, err);
    if (k_Err_has(err)) {
        return;
    }

    log->print_str(log, lvl, msg_prefix, err);
    if (k_Err_has(err)) {
        return;
    }

    print(log, err, lvl, format, args);
    if (k_Err_has(err)) {
        return;
    }

    log->print_ch(log, lvl, '\n', err);
}

static void log_error_callback(intptr_t logger, char* format, ...) {
    struct k_Log* log = (struct k_Log*) logger;
    struct k_Err discard_log_err = K_ERR_INIT;

    va_list args;
    va_start(args, format);
    print_log(log, &discard_log_err, K_LOG_LEVEL_ERROR, format, args);
    va_end(args);
}

void k_Log_print_unsigned_int(
        struct k_Log* log,
        struct k_Err* err,
        enum k_Log_Level lvl,
        unsigned int integer,
        size_t base) {

    if (integer == 0) {
        log->print_ch(log, lvl, NUMERIC_BASE_CONVERSION_SYMBOLS[integer], err);
        return;
    }

    // Reserve 8 chars, which are enough for an 8 bits integer in binary base.
    // If it isn't for a full range integer, call recursively until it is.
    char byte[sizeof(char) * (8 + 1)];
    ssize_t i = STATIC_ARRAY_LEN(byte) - 1 - 1;

    byte[STATIC_ARRAY_LEN(byte) - 1] = '\0';

    while ((i >= 0) && (integer != 0)) {
        byte[i--] = NUMERIC_BASE_CONVERSION_SYMBOLS[integer % base];
        integer /= base;
    }

    if (integer != 0) {
        k_Log_print_unsigned_int(log, err, lvl, integer, base);
        if (k_Err_has(err)) {
            return;
        }
    }

    log->print_str(log, lvl, byte + i + 1, err);
}

void k_Log_err_details(struct k_Log* log, struct k_Err* err) {
    struct k_Err discard_log_err = K_ERR_INIT;

    err->describe(err, log_error_callback, (intptr_t) log);
    k_Log_error(log, &discard_log_err, "  `{s}()` at {s}:{iu}",
        err->function, err->file, err->line);
}

void k_Log_error(
        struct k_Log* log,
        struct k_Err* err,
        char* format,
        ...) {

    va_list args;
    va_start(args, format);
    print_log(log, err, K_LOG_LEVEL_ERROR, format, args);
    va_end(args);
}

void k_Log_warning(
        struct k_Log* log,
        struct k_Err* err,
        char* format,
        ...) {

    va_list args;
    va_start(args, format);
    print_log(log, err, K_LOG_LEVEL_WARN, format, args);
    va_end(args);
}

void k_Log_info(
        struct k_Log* log,
        struct k_Err* err,
        char* format,
        ...) {

    va_list args;
    va_start(args, format);
    print_log(log, err, K_LOG_LEVEL_INFO, format, args);
    va_end(args);
}
