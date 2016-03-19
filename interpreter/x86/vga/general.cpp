#include "../../core/Log.h"
#include "../Bit.h"
#include "../io.h"
#include "general.h"


namespace eon {
namespace x86 {
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

    
    static bool _is_color_mode_enabled = true;


    void enable_color_mode(bool enable) {
        uint8_t status;
        io::read(MISCELLANEOUS_OUTPUT_READ_PORT, 1, &status);

        // Extract the I/O address select bit and infer the compatibility mode.
        bool is_color_mode_enabled = BIT_IS_SET(status, 0);

        if (enable != is_color_mode_enabled) {
            status = enable ? BIT_SET(status, 0) : BIT_CLEAR(status, 0);
            io::write(MISCELLANEOUS_OUTPUT_WRITE_PORT, 1, &status);
        }

        _is_color_mode_enabled = enable;
    }
    
    
    uint8_t read_input_status(uint8_t register_number) {
        uint8_t status = 0;
        
        switch (register_number) {
        case 0:
            io::read(INPUT_STATUS_0_READ_PORT, 1, &status);
            break;
        case 1:
            io::read(
                _is_color_mode_enabled
                    ? COLOR_INPUT_STATUS_1_READ_PORT
                    : MONOCHROME_INPUT_STATUS_1_READ_PORT,
                1,
                &status);
            break;
        default:
            core::Log::get()->error("Invalid VGA general register: {iu}",
                register_number);
            break;
        }
        
        return status;
    }
}}}}
