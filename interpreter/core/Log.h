#pragma once
#include <stdarg.h>
#include <stddef.h>

struct e_Log {
    virtual ~e_Log() {};
    void print(unsigned int integer, size_t base);
    void print(const char* format, va_list arguments);
};

enum {E_LOG_TAB_SIZE_SPACES = 4};
enum e_Log_Level {E_LOG_ERROR, E_LOG_WARN, E_LOG_INFO};

extern struct e_Log* e_Log_get();
extern void e_Log_prepare(struct e_Log* log, enum e_Log_Level level);
extern void e_Log_print_ch(struct e_Log* log, char ch);
extern void e_Log_print_str(struct e_Log* log, const char* string);

/**
 * Log format is a regular string with placeholders denoted by curly braces.
 *
 * Inside each curly brace is a conversion specifier:
 * - "c": character
 * - "s": string or `NULL`
 * - "i": integer
 *   - with "u": unsigned
 *   - with one of:
 *     - "b": base 2
 *     - "h": base 16
 *     - none: base 10
 *
 * To print a literal curly brace, repeat it twice.
 */
void e_Log_msg(
    struct e_Log* log, enum e_Log_Level level, const char* format, ...);
