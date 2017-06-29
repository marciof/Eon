#include <stdio.h>
#include "../core/Log.h"

struct e_Log_FILE {
    FILE* stream;
};

static uint8_t mem[sizeof(struct e_Log) + sizeof(struct e_Log_FILE)];

// FIXME: add colors
static void prepare(struct e_Log* log, enum e_Log_Level level) {
    struct e_Log_FILE* file = (struct e_Log_FILE*) log->val;

    file->stream = (level == E_LOG_ERROR) || (level == E_LOG_WARN)
        ? stderr
        : stdout;
}

static void print_ch(struct e_Log* log, char ch) {
    fputc(ch, ((struct e_Log_FILE*) log->val)->stream);
}

static void print_str(struct e_Log* log, const char* str) {
    fputs(str, ((struct e_Log_FILE*) log->val)->stream);
}

struct e_Log* e_Log_get() {
    static struct e_Log* log = NULL;

    if (log == NULL) {
        log = (struct e_Log*) mem;
        log->prepare = prepare;
        log->print_ch = print_ch;
        log->print_str = print_str;
        ((struct e_Log_FILE*) log->val)->stream = stdout;
    }

    return log;
}
