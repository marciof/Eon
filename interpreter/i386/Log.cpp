#include "../core/Log.h"
#include "vga/Text.h"

class e_Log_Vga: public e_Log {
public:
    e_Log_Vga() {
        e_VGA_Text_init();
    }

    void print(const char* string) {
        e_VGA_Text_print(string);
    }
};

struct e_Log* e_Log_get() {
    static e_Log_Vga log;
    return &log;
}

void e_Log_prepare(struct e_Log* log, enum e_Log_Level level) {
    if (level == E_LOG_ERROR) {
        e_VGA_Text_set_color(E_VGA_TEXT_RED);
    }
    else if (level == E_LOG_WARN) {
        e_VGA_Text_set_color(E_VGA_TEXT_YELLOW);
    }
    else {
        e_VGA_Text_set_color(E_VGA_TEXT_WHITE);
    }
}

void e_Log_print_ch(struct e_Log* log, char ch) {
    e_VGA_Text_print(ch);
}
