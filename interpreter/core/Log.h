#pragma once
#include <stdint.h>
#include "Err.h"

enum {K_LOG_TAB_SIZE_SPACES = 4};
enum k_Log_Level {K_LOG_ERROR, K_LOG_WARN, K_LOG_INFO};

// FIXME: use Ref?
// FIXME: add timestamps?
struct k_Log {
    void (*prepare)(struct k_Log* log, struct k_Err* err, enum k_Log_Level lvl);
    void (*print_ch)(struct k_Log* log, struct k_Err* err, char ch);
    void (*print_str)(struct k_Log* log, struct k_Err* err, const char* str);
    uint8_t val[];
};

extern struct k_Log* k_Log_get(void);

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
    struct k_Log* log,
    struct k_Err* err,
    enum k_Log_Level lvl,
    const char* format, ...);
