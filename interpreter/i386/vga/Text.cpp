#include "../../core/Log.h"
#include "attribute.h"
#include "crt.h"
#include "general.h"
#include "graphics.h"
#include "Text.h"

#define CLEAR_CHARACTER ' '

#define ENCODE_COLOR(foreground, background) \
    (static_cast<uint8_t>(((background) << 4) + (foreground)))

using namespace eon::i386::vga;

static const graphics::Memory_Map* gfx = NULL;
static size_t line = 0;
static size_t column = 0;
static uint8_t color_code = ENCODE_COLOR(TEXT_WHITE, TEXT_BLACK);

static void clear_screen() {
    const size_t END = 2 * gfx->rows * gfx->columns;

    for (size_t i = 0; i < END; i += 2) {
        gfx->start[i] = CLEAR_CHARACTER;
        gfx->start[i + 1] = color_code;
    }
}

static void scroll_screen(int rows = +1) {
    const size_t END = 2 * ((gfx->rows * gfx->columns) + gfx->columns);
    size_t i = 2 * rows * gfx->columns;
    size_t previous = 2 * (rows - 1) * gfx->columns;

    while (i < END) {
        gfx->start[previous++] = gfx->start[i++];
        gfx->start[previous++] = gfx->start[i++];
    }

    // Clear last rows.
    i = 2 * (gfx->rows - rows) * gfx->columns;

    while (i < END) {
        gfx->start[i] = CLEAR_CHARACTER;
        gfx->start[i + 1] = color_code;
        i += 2;
    }
}

size_t e_VGA_Text_get_columns() {
    return gfx->columns;
}

size_t e_VGA_Text_get_rows() {
    return gfx->rows;
}

void e_VGA_Text_init() {
    gfx = graphics::get_memory_map();

    crt::enable_cursor(false);
    clear_screen();
    crt::move_cursor(line, column);
    attribute::enable_blink_mode(false);
    crt::enable_color_mode(gfx->is_color);
    general::enable_color_mode(gfx->is_color);
}

void e_VGA_Text_print(char ch) {
    switch (ch) {
    case '\n':
        ++line;
        column = 0;
        break;
    case '\t':
        column += e_Log::TAB_NR_SPACES - (column % e_Log::TAB_NR_SPACES);
        break;
    default:
        size_t position = 2 * ((line * gfx->columns) + column);
        gfx->start[position] = ch;
        gfx->start[position + 1] = color_code;
        ++column;
        break;
    }

    if (column >= gfx->columns) {
        column = 0;
        ++line;
    }

    if (line >= gfx->rows) {
        --line;
        scroll_screen();
    }
}

void e_VGA_Text_print(const char* string) {
    while (*string != '\0') {
        e_VGA_Text_print(*string++);
    }
}

void e_VGA_Text_set_color(e_VGA_Text_Color foreground,
    e_VGA_Text_Color background) {
    color_code = ENCODE_COLOR(foreground, background);
}
