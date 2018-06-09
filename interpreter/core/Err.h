#pragma once
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define K_ERR_INIT {NULL}

struct k_Err {
    /** Description ends in a newline. */
    void (*describe)(struct k_Err* err);
    const char* function;
    char* file;
    size_t line;
    intptr_t arg;
};

void k_Err_describe(struct k_Err* err);

void k_Err_describe_text(struct k_Err* err);

bool k_Err_has(struct k_Err* err);

void k_Err_reset(struct k_Err* err);

void k_Err_set(
    struct k_Err* err,
    void (*describe)(struct k_Err*),
    const char* function,
    char* file,
    size_t line,
    intptr_t arg);

#define K_ERR_SET(err, describe, arg) \
    k_Err_set( \
        (err), \
        (describe), \
        __func__, \
        __FILE__, \
        __LINE__, \
        (intptr_t) (arg))

#define K_ERR_SET_TEXT(err, text) \
    K_ERR_SET((err), k_Err_describe_text, (text))
