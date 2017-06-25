#include "../core/Log.h"
#include "vga/text_mode.h"

using namespace eon::i386;

class e_Log_Vga: public e_Log {
public:
    e_Log_Vga() {
        vga::text_mode::initialize();
    }

protected:
    void prepare_error() {
        vga::text_mode::set_color(vga::text_mode::RED);
    }

    void prepare_info() {
        vga::text_mode::set_color(vga::text_mode::WHITE);
    }

    void prepare_warning() {
        vga::text_mode::set_color(vga::text_mode::YELLOW);
    }

    void print(char ch) {
        vga::text_mode::print(ch);
    }

    void print(const char* string) {
        vga::text_mode::print(string);
    }
};

e_Log* e_Log::get() {
    static e_Log_Vga log;
    return &log;
}
