#include <stdarg.h>
#include <stddef.h>
#include <sys/types.h>
#include "Log.h"
#include "System.h"

#define NUMERIC_BASE_CONVERSION_SYMBOLS "0123456789ABCDEF"
#define PLACEHOLDER_BEGIN '{'
#define PLACEHOLDER_END '}'

#define ERROR_MESSAGE_PREFIX "[ERROR] "
#define INFO_MESSAGE_PREFIX "[INFO] "
#define WARNING_MESSAGE_PREFIX "[WARN] "

#define FORMAT_STRING_ERROR \
    ERROR_MESSAGE_PREFIX "Invalid logging format string.\n"

#define STATIC_ARRAY_LENGTH(array) \
    (sizeof(array) / sizeof((array)[0]))

static void e_Log_print_int(e_Log log, unsigned int integer, size_t base) {
    if (integer == 0) {
        e_Log_print_ch(log, NUMERIC_BASE_CONVERSION_SYMBOLS[integer]);
        return;
    }

    // Reserve 8 chars, which are enough for an 8 bits integer.
    // If it isn't for a full range integer, call recursively until it is.
    char byte[sizeof(char) * (8 + 1)];
    ssize_t i = STATIC_ARRAY_LENGTH(byte) - 1 - 1;

    byte[STATIC_ARRAY_LENGTH(byte) - 1] = '\0';

    while ((i >= 0) && (integer != 0)) {
        byte[i--] = NUMERIC_BASE_CONVERSION_SYMBOLS[integer % base];
        integer /= base;
    }

    if (integer != 0) {
        e_Log_print_int(log, integer, base);
    }

    e_Log_print_str(log, byte + i + 1);
}

static void e_Log_print(e_Log log, const char* format, va_list args) {
    for (; *format != '\0'; ++format) {
        if (*format == PLACEHOLDER_END) {
            ++format;

            if ((*format != '\0') && (*format == PLACEHOLDER_END)) {
                e_Log_print_ch(log, PLACEHOLDER_END);
                continue;
            }
            else {
                e_Log_print_str(log, "\n" FORMAT_STRING_ERROR);
                e_System::get()->stop(e_System::E_SYSTEM_HALT);
            }
        }
        else if (*format != PLACEHOLDER_BEGIN) {
            e_Log_print_ch(log, *format);
            continue;
        }

        ++format;

        if (*format == PLACEHOLDER_BEGIN) {
            e_Log_print_ch(log, PLACEHOLDER_BEGIN);
            continue;
        }

        char* str;
        int integer;

        switch (*format++) {
        case 'c':
            e_Log_print_ch(log, static_cast<char>(va_arg(args, int)));
            break;
        case 's':
            str = va_arg(args, char*);
            e_Log_print_str(log, str == NULL ? "(null)" : str);
            break;
        case 'i':
            integer = va_arg(args, int);

            if (*format == 'u') {
                ++format;
            }
            else if (integer < 0) {
                e_Log_print_ch(log, '-');
                integer = -integer;
            }

            switch (*format++) {
            case 'b':
                e_Log_print_int(log, static_cast<unsigned>(integer), 2);
                e_Log_print_ch(log, 'b');
                break;
            case 'h':
                e_Log_print_int(log, static_cast<unsigned>(integer), 16);
                e_Log_print_ch(log, 'h');
                break;
            default:
                e_Log_print_int(log, static_cast<unsigned>(integer), 10);
                --format;
                break;
            }

            break;
        default:
            e_Log_print_str(log, "\n" FORMAT_STRING_ERROR);
                e_System::get()->stop(e_System::E_SYSTEM_HALT);
            break;
        }

        if (*format != PLACEHOLDER_END) {
            e_Log_print_str(log, "\n" FORMAT_STRING_ERROR);
            e_System::get()->stop(e_System::E_SYSTEM_HALT);
        }
    }
}

void e_Log_msg(e_Log log, enum e_Log_Level level, const char* format, ...) {
    const char* msg_prefix;
    e_Log_prepare(log, level);

    if (level == E_LOG_ERROR) {
        msg_prefix = ERROR_MESSAGE_PREFIX;
    }
    else if (level == E_LOG_WARN) {
        msg_prefix = WARNING_MESSAGE_PREFIX;
    }
    else {
        msg_prefix = INFO_MESSAGE_PREFIX;
    }

    e_Log_print_str(log, msg_prefix);

    va_list args;
    va_start(args, format);
    e_Log_print(log, format, args);
    va_end(args);
    e_Log_print_ch(log, '\n');

    if (level == E_LOG_ERROR) {
        e_System::get()->stop(e_System::E_SYSTEM_HALT);
    }
}
