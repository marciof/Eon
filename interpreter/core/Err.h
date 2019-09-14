#pragma once
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define K_ERR_INIT {NULL, NULL, NULL, 0, 0}

/**
 * @see k_Log
 */
typedef void (*k_Err_log)(uintptr_t logger, char* format, ...);

struct k_Err {
    void (*describe)(struct k_Err* err, k_Err_log log, uintptr_t logger);
    const char* function;
    char* file;
    size_t line;
    uintptr_t arg;
};

/**
 * @see K_ERR_SET_TEXT
 */
void k_Err_describe_text(struct k_Err*, k_Err_log, uintptr_t);

bool k_Err_has(struct k_Err* err);

/**
 * @see K_ERR_SET
 */
void k_Err_set(
    struct k_Err*,
    void (*)(struct k_Err*, k_Err_log, uintptr_t),
    const char*,
    char*,
    size_t,
    uintptr_t);

#define K_ERR_SET(err, describe, arg) \
    k_Err_set( \
        (err), \
        (describe), \
        __func__, \
        __FILE__, \
        __LINE__, \
        (uintptr_t) (arg))

#define K_ERR_SET_TEXT(err, text) \
    K_ERR_SET((err), k_Err_describe_text, (text))
