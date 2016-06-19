#include "../../core/log.h"
#include "attribute.h"
#include "crt.h"
#include "general.h"
#include "graphics.h"
#include "text_mode.h"


#define CLEAR_CHARACTER ' '

#define ENCODE_COLOR(foreground, background) \
    (static_cast<uint8_t>(((background) << 4) + (foreground)))


namespace eon {
namespace x86 {
namespace vga {
namespace text_mode {

    static const graphics::Memory_Map* _gfx = NULL;
    static size_t _row = 0;
    static size_t _column = 0;
    static uint8_t _color_code = ENCODE_COLOR(WHITE, BLACK);


    static void clear_screen() {
        const size_t END = 2 * _gfx->rows * _gfx->columns;

        for (size_t i = 0; i < END; i += 2) {
            _gfx->start[i] = CLEAR_CHARACTER;
            _gfx->start[i + 1] = _color_code;
        }
    }
    
    
    static void scroll_screen(int rows = +1) {
        const size_t END = 2 * ((_gfx->rows * _gfx->columns) + _gfx->columns);
        size_t i = 2 * rows * _gfx->columns;
        size_t previous = 2 * (rows - 1) * _gfx->columns;

        while (i < END) {
            _gfx->start[previous++] = _gfx->start[i++];
            _gfx->start[previous++] = _gfx->start[i++];
        }
        
        // Clear last rows.
        i = 2 * (_gfx->rows - rows) * _gfx->columns;

        while (i < END) {
            _gfx->start[i] = CLEAR_CHARACTER;
            _gfx->start[i + 1] = _color_code;
            i += 2;
        }
    }
    
    
    size_t get_columns() {
        return _gfx->columns;
    }
    
    
    size_t get_rows() {
        return _gfx->rows;
    }
    
    
    void initialize() {
        _gfx = graphics::get_memory_map();

        crt::enable_cursor(false);
        clear_screen();
        crt::move_cursor(_row, _column);
        attribute::enable_blink_mode(false);
        crt::enable_color_mode(_gfx->is_color);
        general::enable_color_mode(_gfx->is_color);
    }
    
    
    void print(char ch) {
        switch (ch) {
        case '\n':
            ++_row;
            _column = 0;
            break;
        case '\t':
            _column += core::Log::TAB_NR_SPACES
                - (_column % core::Log::TAB_NR_SPACES);
            break;
        default:
            size_t position = 2 * ((_row * _gfx->columns) + _column);
            _gfx->start[position] = ch;
            _gfx->start[position + 1] = _color_code;
            ++_column;
            break;
        }
        
        if (_column >= _gfx->columns) {
            _column = 0;
            ++_row;
        }
        
        if (_row >= _gfx->rows) {
            --_row;
            scroll_screen();
        }
    }
    
    
    void print(const char* string) {
        while (*string != '\0') {
            print(*string++);
        }
    }


    void set_color(Color foreground, Color background) {
        _color_code = ENCODE_COLOR(foreground, background);
    }
}}}}
