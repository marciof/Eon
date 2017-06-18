#include "../../core/log.h"
#include "../bit.h"
#include "../io.h"
#include "general.h"

namespace eon {
namespace i386 {
namespace vga {
namespace general {
    typedef uint16_t Port;
    enum {
        MISCELLANEOUS_OUTPUT_WRITE_PORT = 0x3C2,
        MISCELLANEOUS_OUTPUT_READ_PORT = 0x3CC,
        FEATURE_CONTROL_READ_PORT = 0x3CA,
        INPUT_STATUS_0_READ_PORT = 0x3C2,

        COLOR_FEATURE_CONTROL_WRITE_PORT = 0x3DA,
        COLOR_INPUT_STATUS_1_READ_PORT = 0x3DA,

        MONOCHROME_FEATURE_CONTROL_WRITE_PORT = 0x3BA,
        MONOCHROME_INPUT_STATUS_1_READ_PORT = 0x3BA
    };

    static bool is_color_mode_enabled = true;

    void enable_color_mode(bool enable) {
        uint8_t status = io::read_byte(MISCELLANEOUS_OUTPUT_READ_PORT);

        // Extract the I/O address select bit and infer the compatibility mode.
        if (enable != BIT_IS_SET(status, 0)) {
            io::write_byte(MISCELLANEOUS_OUTPUT_WRITE_PORT,
                static_cast<uint8_t>(enable
                ? BIT_SET(status, 0)
                : BIT_CLEAR(status, 0)));
        }

        is_color_mode_enabled = enable;
    }

    uint8_t read_input_status(uint8_t register_number) {
        switch (register_number) {
        case 0:
            return io::read_byte(INPUT_STATUS_0_READ_PORT);
        case 1:
            return io::read_byte(
                is_color_mode_enabled
                    ? COLOR_INPUT_STATUS_1_READ_PORT
                    : MONOCHROME_INPUT_STATUS_1_READ_PORT);
        default:
            core::Log::get()->error("Invalid VGA general register: {iu}",
                register_number);
            return 0;
        }
    }
}}}}
