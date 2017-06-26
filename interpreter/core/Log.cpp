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

void e_Log_msg(
        struct e_Log* log, enum e_Log_Level level, const char* format, ...) {

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

    va_list arguments;
    va_start(arguments, format);
    e_Log_get()->print(format, arguments);
    va_end(arguments);
    e_Log_print_ch(log, '\n');

    if (level == E_LOG_ERROR) {
        e_System::get()->stop(e_System::E_SYSTEM_HALT);
    }
}

void e_Log::print(unsigned int integer, size_t base) {
    if (integer == 0) {
        e_Log_print_ch(this, NUMERIC_BASE_CONVERSION_SYMBOLS[integer]);
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
        this->print(integer, base);
    }

    e_Log_print_str(this, byte + i + 1);
}

void e_Log::print(const char* format, va_list arguments) {
    for (; *format != '\0'; ++format) {
        if (*format == PLACEHOLDER_END) {
            ++format;

            if ((*format != '\0') && (*format == PLACEHOLDER_END)) {
                e_Log_print_ch(this, PLACEHOLDER_END);
                continue;
            }
            else {
                e_Log_print_str(this, "\n" FORMAT_STRING_ERROR);
                e_System::get()->stop(e_System::E_SYSTEM_HALT);
            }
        }
        else if (*format != PLACEHOLDER_BEGIN) {
            e_Log_print_ch(this, *format);
            continue;
        }

        ++format;

        if (*format == PLACEHOLDER_BEGIN) {
            e_Log_print_ch(this, PLACEHOLDER_BEGIN);
            continue;
        }

        char* string;
        int integer;

        switch (*format++) {
        case 'c':
            e_Log_print_ch(this, static_cast<char>(va_arg(arguments, int)));
            break;
        case 's':
            string = va_arg(arguments, char*);
            e_Log_print_str(this, string == NULL ? "(null)" : string);
            break;
        case 'i':
            integer = va_arg(arguments, int);

            if (*format == 'u') {
                ++format;
            }
            else if (integer < 0) {
                e_Log_print_ch(this, '-');
                integer = -integer;
            }

            switch (*format++) {
            case 'b':
                this->print(integer, 2);
                e_Log_print_ch(this, 'b');
                break;
            case 'h':
                this->print(integer, 16);
                e_Log_print_ch(this, 'h');
                break;
            default:
                this->print(integer, 10);
                --format;
                break;
            }

            break;
        default:
            e_Log_print_str(this, "\n" FORMAT_STRING_ERROR);
                e_System::get()->stop(e_System::E_SYSTEM_HALT);
            break;
        }

        if (*format != PLACEHOLDER_END) {
            e_Log_print_str(this, "\n" FORMAT_STRING_ERROR);
            e_System::get()->stop(e_System::E_SYSTEM_HALT);
        }
    }
}
