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

e_Log* e_Log::get() {
    static e_Log_Stdout log;
    return &log;
}
