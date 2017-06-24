#pragma once
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include "Any.h"

#define ERR_INIT_VAL {NULL}
#define ERR_STACK_LEN 8

#define ERR_HAS(err) \
    ((err)->stack[0].describe != NULL)

#define ERR_ADD_CSTRING(err, message) \
    Err_add( \
        (err), \
        Any_ptr((message)), \
        __func__, \
        __FILE__, \
        __LINE__, \
        Err_describe_cstring)

#define ERR_ADD_ERRNO(err, nr) \
    Err_add( \
        (err), \
        Any_val((nr)), \
        __func__, \
        __FILE__, \
        __LINE__, \
        Err_describe_errno)

struct Err_Item {
    union Any arg;
    const char* function;
    const char* file;
    size_t line;
    char* (*describe)(union Any arg);
};

struct Err {
    struct Err_Item stack[ERR_STACK_LEN];
};

void* Err_add(
    struct Err* err,
    union Any arg,
    const char* function,
    const char* file,
    size_t line,
    char* (*describe)(union Any));

char* Err_describe_cstring(union Any arg);
char* Err_describe_errno(union Any arg);
void Err_print(struct Err* err, FILE* stream);
