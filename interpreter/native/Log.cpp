#include <stdio.h>
#include "../core/Log.h"

class e_Log_Stdout: public e_Log {
    void print(const char* string) {
        // FIXME: use stdout for info only
        printf("%s", string);
    }
};

struct e_Log* e_Log_get() {
    static e_Log_Stdout log;
    return &log;
}

void e_Log_prepare(struct e_Log* log, enum e_Log_Level level) {
    // FIXME: add colors
}

void e_Log_print_ch(struct e_Log* log, char ch) {
    // FIXME: use stdout for info only
    putchar(ch);
}
