#include "../core/Bit.h"
#include "../core/Log.h"
#include "vga/Text.h"

static void prepare(
        K_BIT_UNUSED(struct k_Log* log),
        K_BIT_UNUSED(struct k_Err* err),
        enum k_Log_Level lvl) {

    if (lvl == K_LOG_ERROR) {
        k_VGA_Text_set_color(K_VGA_TEXT_RED, K_VGA_TEXT_BLACK);
    }
    else if (lvl == K_LOG_WARN) {
        k_VGA_Text_set_color(K_VGA_TEXT_YELLOW, K_VGA_TEXT_BLACK);
    }
    else {
        k_VGA_Text_set_color(K_VGA_TEXT_WHITE, K_VGA_TEXT_BLACK);
    }
}

static void print_ch(
        K_BIT_UNUSED(struct k_Log* log),
        K_BIT_UNUSED(struct k_Err* err),
        char ch) {

    k_VGA_Text_print_ch(ch);
}

static void print_str(
        K_BIT_UNUSED(struct k_Log* log),
        K_BIT_UNUSED(struct k_Err* err),
        const char* str) {

    k_VGA_Text_print_str(str);
}

struct k_Log* k_Log_get(void) {
    static struct k_Log log = {prepare, print_ch, print_str};
    return &log;
}
