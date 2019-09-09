#include <stdarg.h>
#include <stddef.h>
#include <sys/types.h>
#include "Log.h"

#define NUMERIC_BASE_CONVERSION_SYMBOLS "0123456789ABCDEF"
#define PLACEHOLDER_BEGIN '{'
#define PLACEHOLDER_END '}'
#define FORMAT_STR_ERROR "Invalid logging format string"
#define STATIC_ARRAY_LEN(array) (sizeof((array)) / sizeof((array)[0]))

static void print_int(
        struct k_Log* log,
        enum k_Log_Level lvl,
        unsigned int integer,
        size_t base,
        struct k_Err* err) {

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
        print_int(log, lvl, integer, base, err);
        if (k_Err_has(err)) {
            return;
        }
    }

    log->print_str(log, lvl, byte + i + 1, err);
}

// FIXME: too long, refactor
static void print(
        struct k_Log* log,
        enum k_Log_Level lvl,
        const char* format,
        va_list args,
        struct k_Err* err) {

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
        int integer;

        switch (*format++) {
        case 'c':
            log->print_ch(log, lvl, (char) va_arg(args, int), err);
            break;
        case 's':
            str = va_arg(args, char*);
            log->print_str(log, lvl, str == NULL ? "(null)" : str, err);
            break;
        case 'i':
            integer = va_arg(args, int);

            if (*format == 'u') {
                ++format;
            }
            else if (integer < 0) {
                log->print_ch(log, lvl, '-', err);
                if (k_Err_has(err)) {
                    return;
                }
                integer = -integer;
            }

            switch (*format++) {
            case 'b':
                print_int(log, lvl, (unsigned) integer, 2, err);
                if (k_Err_has(err)) {
                    return;
                }
                log->print_ch(log, lvl, 'b', err);
                break;
            case 'h':
                print_int(log, lvl, (unsigned) integer, 16, err);
                if (k_Err_has(err)) {
                    return;
                }
                log->print_ch(log, lvl, 'h', err);
                break;
            default:
                print_int(log, lvl, (unsigned) integer, 10, err);
                --format;
                break;
            }

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

// FIXME: refactor duplicate code with `k_Log_msg`
static void k_Log_msg_list(
        struct k_Log* log,
        struct k_Err* err,
        enum k_Log_Level lvl,
        const char* format,
        va_list args) {

    char* msg_prefix;

    if (lvl == K_LOG_ERROR) {
        msg_prefix = "[ERROR] ";
    }
    else if (lvl == K_LOG_WARN) {
        msg_prefix = "[WARN] ";
    }
    else {
        msg_prefix = "[INFO] ";
    }

    log->print_str(log, lvl, msg_prefix, err);
    if (k_Err_has(err)) {
        return;
    }

    print(log, lvl, format, args, err);

    if (k_Err_has(err)) {
        return;
    }

    log->print_ch(log, lvl, '\n', err);
}

// FIXME: refactor
static void k_Log_err_log(intptr_t logger, const char* format, ...) {
    struct k_Log* log = (struct k_Log*) logger;
    struct k_Err discard_log_err = K_ERR_INIT;

    va_list args;
    va_start(args, format);
    k_Log_msg_list(log, &discard_log_err, K_LOG_ERROR, format, args);
    va_end(args);
}

void k_Log_error(struct k_Log* log, struct k_Err* err) {
    struct k_Err discard_log_err = K_ERR_INIT;

    err->describe(err, k_Log_err_log, (intptr_t) log);
    k_Log_msg(log, &discard_log_err, K_LOG_ERROR,
        "  `{s}()` at {s}:{iu}", err->function, err->file, err->line);
}

void k_Log_msg(
        struct k_Log* log,
        struct k_Err* err,
        enum k_Log_Level lvl,
        const char* format,
        ...) {

    char* msg_prefix;

    if (lvl == K_LOG_ERROR) {
        msg_prefix = "[ERROR] ";
    }
    else if (lvl == K_LOG_WARN) {
        msg_prefix = "[WARN] ";
    }
    else {
        msg_prefix = "[INFO] ";
    }

    log->print_str(log, lvl, msg_prefix, err);
    if (k_Err_has(err)) {
        return;
    }

    va_list args;
    va_start(args, format);
    print(log, lvl, format, args, err);
    va_end(args);

    if (k_Err_has(err)) {
        return;
    }

    log->print_ch(log, lvl, '\n', err);
}
