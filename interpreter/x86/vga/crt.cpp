#include "../Bit.h"
#include "../io.h"
#include "crt.h"
#include "text_mode.h"

namespace eon {
namespace x86 {
namespace vga {
namespace crt {
    typedef uint16_t Port;
    enum {
        COLOR_ADDRESS_PORT = 0x3D4,
        COLOR_DATA_PORT = 0x3D5,

        MONOCHROME_ADDRESS_PORT = 0x3B4,
        MONOCHROME_DATA_PORT = 0x3B5
    };

    static bool is_color_mode_enabled = true;

    void enable_color_mode(bool enable) {
        is_color_mode_enabled = enable;
    }

    void enable_cursor(bool enable) {
        uint8_t status = read(CURSOR_START);
        
        write(CURSOR_START, static_cast<uint8_t>(enable
            ? BIT_CLEAR(status, 5)
            : BIT_SET(status, 5)));
    }

    void move_cursor(uint32_t row, uint32_t column) {
        size_t columns = text_mode::get_columns();
        uint16_t position = static_cast<uint16_t>((row * columns) + column);
        
        write(CURSOR_LOCATION_LOW, static_cast<uint8_t>(position & 0xFF));
        write(CURSOR_LOCATION_HIGH, static_cast<uint8_t>(position >> 8));
    }
    
    uint8_t read(Register reg) {
        io::write_byte(
            is_color_mode_enabled
                ? COLOR_ADDRESS_PORT
                : MONOCHROME_ADDRESS_PORT,
            reg);

        return io::read_byte(
            is_color_mode_enabled
                ? COLOR_DATA_PORT
                : MONOCHROME_DATA_PORT);
    }
    
    void write(Register reg, uint8_t data) {
        io::write_byte(
            is_color_mode_enabled
                ? COLOR_ADDRESS_PORT
                : MONOCHROME_ADDRESS_PORT,
            reg);

        io::write_byte(
            is_color_mode_enabled
                ? COLOR_DATA_PORT
                : MONOCHROME_DATA_PORT,
            data);
    }
}}}}
