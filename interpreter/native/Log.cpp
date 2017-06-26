#include <stdio.h>
#include "../core/Log.h"

e_Log e_Log_get() {
    return e_Any_ptr(NULL);
}

void e_Log_prepare(e_Log log, enum e_Log_Level level) {
    // FIXME: add colors
    // FIXME: use `stdout` and `stderr` according to `level`
}

void e_Log_print_ch(e_Log log, char ch) {
    putchar(ch);
}

void e_Log_print_str(e_Log log, const char* str) {
    fputs(str, stdout);
}
