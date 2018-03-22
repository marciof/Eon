#include <stdio.h>
#include "../core/Log.h"

struct Log_FILE {
    FILE* stream;
};

static uint8_t mem[sizeof(struct k_Log) + sizeof(struct Log_FILE)];

// FIXME: add colors
static void prepare(struct k_Log* log, enum k_Log_Level level) {
    struct Log_FILE* file = (struct Log_FILE*) log->val;

    file->stream = (level == K_LOG_ERROR) || (level == K_LOG_WARN)
        ? stderr
        : stdout;
}

static void print_ch(struct k_Log* log, char ch) {
    fputc(ch, ((struct Log_FILE*) log->val)->stream);
}

static void print_str(struct k_Log* log, const char* str) {
    fputs(str, ((struct Log_FILE*) log->val)->stream);
}

struct k_Log* k_Log_get() {
    static struct k_Log* log = NULL;

    if (log == NULL) {
        log = (struct k_Log*) mem;
        log->prepare = prepare;
        log->print_ch = print_ch;
        log->print_str = print_str;
        ((struct Log_FILE*) log->val)->stream = stdout;
    }

    return log;
}
