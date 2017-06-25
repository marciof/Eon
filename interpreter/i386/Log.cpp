#include "../core/Log.h"
#include "vga/Text.h"

class e_Log_Vga: public e_Log {
public:
    e_Log_Vga() {
        e_VGA_Text_init();
    }

protected:
    void prepare_error() {
        e_VGA_Text_set_color(VGA_TEXT_RED);
    }

    void prepare_info() {
        e_VGA_Text_set_color(VGA_TEXT_WHITE);
    }

    void prepare_warning() {
        e_VGA_Text_set_color(VGA_TEXT_YELLOW);
    }

    void print(char ch) {
        e_VGA_Text_print(ch);
    }

    void print(const char* string) {
        e_VGA_Text_print(string);
    }
};

e_Log* e_Log::get() {
    static e_Log_Vga log;
    return &log;
}
