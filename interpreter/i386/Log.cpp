#include "../core/Log.h"
#include "vga/Text.h"

static void prepare(struct e_Log* log, enum e_Log_Level level) {
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

static void print_ch(struct e_Log* log, char ch) {
    e_VGA_Text_print(ch);
}

static void print_str(struct e_Log* log, const char* str) {
    e_VGA_Text_print(str);
}

// FIXME: remove globals in VGA and use this instance instead?
struct e_Log* e_Log_get() {
    static struct e_Log log = {prepare, print_ch, print_str};
    return &log;
}
