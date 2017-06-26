#include <iostream>
#include "../core/Log.h"

class e_Log_Stdout: public e_Log {
protected:
    void print(char ch) {
        std::cout << ch;
    }

    void print(const char* string) {
        std::cout << string;
    }
};

struct e_Log* e_Log_get() {
    static e_Log_Stdout log;
    return &log;
}

void e_Log_prepare(struct e_Log* log, enum e_Log_Level level) {
    // FIXME: add colors
}
