#include "../core/Bit.h"
#include "../core/Log.h"
#include "vga/Text.h"

static void prepare(
        K_BIT_ATTR_UNUSED(struct k_Log* log), enum k_Log_Level level) {

    if (level == K_LOG_ERROR) {
        k_VGA_Text_set_color(K_VGA_TEXT_RED, K_VGA_TEXT_BLACK);
    }
    else if (level == K_LOG_WARN) {
        k_VGA_Text_set_color(K_VGA_TEXT_YELLOW, K_VGA_TEXT_BLACK);
    }
    else {
        k_VGA_Text_set_color(K_VGA_TEXT_WHITE, K_VGA_TEXT_BLACK);
    }
}

static void print_ch(K_BIT_ATTR_UNUSED(struct k_Log* log), char ch) {
    k_VGA_Text_print_ch(ch);
}

static void print_str(K_BIT_ATTR_UNUSED(struct k_Log* log), const char* str) {
    k_VGA_Text_print_str(str);
}

// FIXME: remove globals in VGA and use this instance instead?
struct k_Log* k_Log_get() {
    static struct k_Log log = {prepare, print_ch, print_str};
    return &log;
}
