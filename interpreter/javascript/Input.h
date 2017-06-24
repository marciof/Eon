#pragma once
#include "Any.h"
#include "Err.h"
#include "Ref.h"
#include "Str.h"

struct Input {
    union Any arg;
    char* location;
    struct Str* (*read)(union Any arg, bool* has_err);
    REF_FIELDS;
};

struct Input* Input_from_stdin(bool* has_err);
