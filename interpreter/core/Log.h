#pragma once
#include "Any.h"

typedef union e_Any e_Log;

enum {E_LOG_TAB_SIZE_SPACES = 4};
enum e_Log_Level {E_LOG_ERROR, E_LOG_WARN, E_LOG_INFO};

// FIXME: use methods instead, as this doesn't allow implementations to co-exist
extern e_Log e_Log_get();
extern void e_Log_prepare(e_Log log, enum e_Log_Level level);
extern void e_Log_print_ch(e_Log log, char ch);
extern void e_Log_print_str(e_Log log, const char* str);

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
void e_Log_msg(e_Log log, enum e_Log_Level level, const char* format, ...);
