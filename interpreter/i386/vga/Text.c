#include "../../core/Log.h"
#include "Attr.h"
#include "CRT.h"
#include "Extern.h"
#include "Gfx.h"
#include "Text.h"

#define CLEAR_CHAR ' '

#define ENCODE_COLOR(foreground, background) \
    ((uint8_t) (((background) << 4) + (foreground)))

static const struct k_VGA_Gfx_Memory_Map* gfx = NULL;
static size_t line = 0;
static size_t column = 0;
static uint8_t color_code = ENCODE_COLOR(K_VGA_TEXT_WHITE, K_VGA_TEXT_BLACK);

static void clear_screen(void) {
    const size_t END = 2 * gfx->lines * gfx->columns;

    for (size_t i = 0; i < END; i += 2) {
        gfx->start[i] = CLEAR_CHAR;
        gfx->start[i + 1] = color_code;
    }
}

static void scroll_screen(int lines) {
    const size_t END = 2 * ((gfx->lines * gfx->columns) + gfx->columns);
    size_t i = 2 * lines * gfx->columns;
    size_t previous = 2 * (lines - 1) * gfx->columns;

    while (i < END) {
        gfx->start[previous++] = gfx->start[i++];
        gfx->start[previous++] = gfx->start[i++];
    }

    // Clear last lines.
    i = 2 * (gfx->lines - lines) * gfx->columns;

    while (i < END) {
        gfx->start[i] = CLEAR_CHAR;
        gfx->start[i + 1] = color_code;
        i += 2;
    }
}

size_t k_VGA_Text_get_columns(void) {
    return gfx->columns;
}

size_t k_VGA_Text_get_lines(void) {
    return gfx->lines;
}

void k_VGA_Text_init(void) {
    gfx = k_VGA_Gfx_get_memory_map();

    k_VGA_CRT_enable_cursor(false);
    clear_screen();
    k_VGA_CRT_move_cursor(line, column);
    k_VGA_Attr_enable_text_blink_mode(false);
    k_VGA_CRT_enable_color_mode(gfx->is_color);
    k_VGA_Extern_enable_color_mode(gfx->is_color);
}

void k_VGA_Text_print_ch(char ch) {
    size_t position;

    switch (ch) {
    case '\n':
        ++line;
        column = 0;
        break;
    case '\t':
        column += K_LOG_TAB_SIZE_SPACES - (column % K_LOG_TAB_SIZE_SPACES);
        break;
    default:
        position = 2 * ((line * gfx->columns) + column);
        gfx->start[position] = (uint8_t) ch;
        gfx->start[position + 1] = color_code;
        ++column;
        break;
    }

    if (column >= gfx->columns) {
        column = 0;
        ++line;
    }

    if (line >= gfx->lines) {
        --line;
        scroll_screen(+1);
    }
}

void k_VGA_Text_print_str(const char* string) {
    while (*string != '\0') {
        k_VGA_Text_print_ch(*string++);
    }
}

void k_VGA_Text_set_color(k_VGA_Text_Color foreground,
    k_VGA_Text_Color background) {
    color_code = ENCODE_COLOR(foreground, background);
}
