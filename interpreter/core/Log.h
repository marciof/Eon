#pragma once
#include <stdint.h>

enum {K_LOG_TAB_SIZE_SPACES = 4};
enum k_Log_Level {K_LOG_ERROR, K_LOG_WARN, K_LOG_INFO};

// FIXME: use ref?
// FIXME: add timestamps?
struct k_Log {
    void (*prepare)(struct k_Log* log, enum k_Log_Level level);
    void (*print_ch)(struct k_Log* log, char ch);
    void (*print_str)(struct k_Log* log, const char* str);
    uint8_t val[];
};

extern struct k_Log* k_Log_get();

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
void k_Log_msg(
    struct k_Log* log, enum k_Log_Level level, const char* format, ...);
