#include "../core/Log.h"
#include "vga/Text.h"

e_Log e_Log_get() {
    // FIXME: remove globals in VGA and use this instance instead?
    return e_Any_ptr(NULL);
}

void e_Log_prepare(e_Log log, enum e_Log_Level level) {
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

void e_Log_print_ch(e_Log log, char ch) {
    e_VGA_Text_print(ch);
}

void e_Log_print_str(e_Log log, const char* str) {
    e_VGA_Text_print(str);
}
