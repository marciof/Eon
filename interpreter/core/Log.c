#include <stdarg.h>
#include <stddef.h>
#include <sys/types.h>
#include "Log.h"
#include "System.h"

#define NUMERIC_BASE_CONVERSION_SYMBOLS "0123456789ABCDEF"
#define PLACEHOLDER_BEGIN '{'
#define PLACEHOLDER_END '}'

#define ERROR_MSG_PREFIX "[ERROR] "
#define FORMAT_STR_ERROR ERROR_MSG_PREFIX "Invalid logging format string.\n"

#define STATIC_ARRAY_LEN(array) (sizeof((array)) / sizeof((array)[0]))

static void print_int(struct k_Log* log, unsigned int integer, size_t base) {
    if (integer == 0) {
        log->print_ch(log, NUMERIC_BASE_CONVERSION_SYMBOLS[integer]);
        return;
    }

    // Reserve 8 chars, which are enough for an 8 bits integer.
    // If it isn't for a full range integer, call recursively until it is.
    char byte[sizeof(char) * (8 + 1)];
    ssize_t i = STATIC_ARRAY_LEN(byte) - 1 - 1;

    byte[STATIC_ARRAY_LEN(byte) - 1] = '\0';

    while ((i >= 0) && (integer != 0)) {
        byte[i--] = NUMERIC_BASE_CONVERSION_SYMBOLS[integer % base];
        integer /= base;
    }

    if (integer != 0) {
        print_int(log, integer, base);
    }

    log->print_str(log, byte + i + 1);
}

static void print(struct k_Log* log, const char* format, va_list args) {
    for (; *format != '\0'; ++format) {
        if (*format == PLACEHOLDER_END) {
            ++format;

            if ((*format != '\0') && (*format == PLACEHOLDER_END)) {
                log->print_ch(log, PLACEHOLDER_END);
                continue;
            }
            else {
                log->print_str(log, "\n" FORMAT_STR_ERROR);
                k_System_get()->stop(k_System_get(), K_SYSTEM_HALT);
            }
        }
        else if (*format != PLACEHOLDER_BEGIN) {
            log->print_ch(log, *format);
            continue;
        }

        ++format;

        if (*format == PLACEHOLDER_BEGIN) {
            log->print_ch(log, PLACEHOLDER_BEGIN);
            continue;
        }

        char* str;
        int integer;

        switch (*format++) {
        case 'c':
            log->print_ch(log, (char) va_arg(args, int));
            break;
        case 's':
            str = va_arg(args, char*);
            log->print_str(log, str == NULL ? "(null)" : str);
            break;
        case 'i':
            integer = va_arg(args, int);

            if (*format == 'u') {
                ++format;
            }
            else if (integer < 0) {
                log->print_ch(log, '-');
                integer = -integer;
            }

            switch (*format++) {
            case 'b':
                print_int(log, (unsigned) integer, 2);
                log->print_ch(log, 'b');
                break;
            case 'h':
                print_int(log, (unsigned) integer, 16);
                log->print_ch(log, 'h');
                break;
            default:
                print_int(log, (unsigned) integer, 10);
                --format;
                break;
            }

            break;
        default:
            log->print_str(log, "\n" FORMAT_STR_ERROR);
            k_System_get()->stop(k_System_get(), K_SYSTEM_HALT);
            break;
        }

        if (*format != PLACEHOLDER_END) {
            log->print_str(log, "\n" FORMAT_STR_ERROR);
            k_System_get()->stop(k_System_get(), K_SYSTEM_HALT);
        }
    }
}

void k_Log_msg(
        struct k_Log* log, enum k_Log_Level level, const char* format, ...) {

    const char* msg_prefix;
    log->prepare(log, level);

    if (level == K_LOG_ERROR) {
        msg_prefix = ERROR_MSG_PREFIX;
    }
    else if (level == K_LOG_WARN) {
        msg_prefix = "[WARN] ";
    }
    else {
        msg_prefix = "[INFO] ";
    }

    log->print_str(log, msg_prefix);

    va_list args;
    va_start(args, format);
    print(log, format, args);
    va_end(args);
    log->print_ch(log, '\n');

    if (level == K_LOG_ERROR) {
        k_System_get()->stop(k_System_get(), K_SYSTEM_HALT);
    }
}
