#include "../../core/bit.h"
#include "Log.h"
#include "Text.h"

static void set_color(enum k_Log_Level lvl) {
    if (lvl == K_LOG_LEVEL_ERROR) {
        k_VGA_Text_set_color(K_VGA_TEXT_RED, K_VGA_TEXT_BLACK);
    }
    else if (lvl == K_LOG_LEVEL_WARN) {
        k_VGA_Text_set_color(K_VGA_TEXT_YELLOW, K_VGA_TEXT_BLACK);
    }
    else {
        k_VGA_Text_set_color(K_VGA_TEXT_WHITE, K_VGA_TEXT_BLACK);
    }
}

static void print_ch(
        K_BIT_UNUSED(struct k_Log* log),
        enum k_Log_Level lvl,
        char ch,
        K_BIT_UNUSED(struct k_Err* err)) {

    set_color(lvl);
    k_VGA_Text_print_ch(ch);
}

static void print_str(
        K_BIT_UNUSED(struct k_Log* log),
        enum k_Log_Level lvl,
        char* str,
        K_BIT_UNUSED(struct k_Err* err)) {

    set_color(lvl);
    k_VGA_Text_print_str(str);
}

static void print_timestamp(
        struct k_Log* log,
        enum k_Log_Level lvl,
        struct k_Err* err) {

    ++log->value;
    set_color(lvl);
    k_Log_print_unsigned_int(log, err, lvl, log->value, 10);
}

void k_VGA_Log_init(struct k_Log* log) {
    k_VGA_Text_init();

    log->print_ch = print_ch;
    log->print_str = print_str;
    log->print_timestamp = print_timestamp;
    log->value = 0;
}
