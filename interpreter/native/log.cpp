#include <iostream>
#include "../core/log.h"

namespace eon {
namespace native {
    class Stdout_Log: public core::Log {
    protected:
        void print(char ch) {
            std::cout << ch;
        }

        void print(const char* string) {
            std::cout << string;
        }
    };
}}

namespace eon {
namespace core {
    Log* Log::get() {
        static native::Stdout_Log log;
        return &log;
    }
}}
