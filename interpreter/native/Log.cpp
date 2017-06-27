#include <stdio.h>
#include "../core/Log.h"

struct e_Log_FILE {
    FILE* stream;
};

e_Log e_Log_get() {
    static e_Log_FILE log = {stdout};
    return e_Any_ptr(&log);
}

// FIXME: add colors
void e_Log_prepare(e_Log log, enum e_Log_Level level) {
    struct e_Log_FILE* file = static_cast<struct e_Log_FILE*>(log.ptr);

    file->stream = (level == E_LOG_ERROR) || (level == E_LOG_WARN)
        ? stderr
        : stdout;
}

void e_Log_print_ch(e_Log log, char ch) {
    fputc(ch, static_cast<struct e_Log_FILE*>(log.ptr)->stream);
}

void e_Log_print_str(e_Log log, const char* str) {
    fputs(str, static_cast<struct e_Log_FILE*>(log.ptr)->stream);
}
