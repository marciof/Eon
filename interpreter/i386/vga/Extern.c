#include "../../core/Log.h"
#include "../Bit.h"
#include "../IO.h"
#include "Extern.h"

typedef uint16_t Port;
enum {
    MISC_OUTPUT_WRITE_PORT = 0x3C2,
    MISC_OUTPUT_READ_PORT = 0x3CC,
    FEATURE_CONTROL_READ_PORT = 0x3CA,
    INPUT_STATUS_0_READ_PORT = 0x3C2,

    COLOR_FEATURE_CONTROL_WRITE_PORT = 0x3DA,
    COLOR_INPUT_STATUS_1_READ_PORT = 0x3DA,

    MONOCHROME_FEATURE_CONTROL_WRITE_PORT = 0x3BA,
    MONOCHROME_INPUT_STATUS_1_READ_PORT = 0x3BA,
};

static bool is_color_mode_enabled = true;

void e_VGA_Extern_enable_color_mode(bool enable) {
    uint8_t status = e_IO_read_byte(MISC_OUTPUT_READ_PORT);

    // Extract the I/O address select bit and infer the compatibility mode.
    if (enable != E_BIT_IS_SET(status, E_BIT(0))) {
        e_IO_write_byte(MISC_OUTPUT_WRITE_PORT, (uint8_t) (enable
            ? (status | E_BIT(0))
            : E_BIT_CLEAR(status, E_BIT(0))));
    }

    is_color_mode_enabled = enable;
}

uint8_t e_VGA_Extern_read_input_status(uint8_t register_num) {
    switch (register_num) {
    case 0:
        return e_IO_read_byte(INPUT_STATUS_0_READ_PORT);
    case 1:
        return e_IO_read_byte(is_color_mode_enabled
            ? COLOR_INPUT_STATUS_1_READ_PORT
            : MONOCHROME_INPUT_STATUS_1_READ_PORT);
    default:
        e_Log_msg(e_Log_get(), E_LOG_ERROR,
            "Invalid VGA general register: {iu}", register_num);
        return 0;
    }
}
