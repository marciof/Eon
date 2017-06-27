/**
 * @see http://www.intel.com/products/processor/manuals/
 */

#include "../core/Log.h"
#include "../core/System.h"
#include "multiboot/Info.h"
#include "support.h"
#include "vga/Text.h"

/**
 * Interfaces the assembly and C++ source code.
 */
extern "C" void c_main() {
    eon::i386::support::initialize();
    e_VGA_Text_init();
    e_Multiboot_Info::get()->log();
    e_System_stop(e_System_get());
}

/**
 * Halts the computer.
 */
extern "C" void e_System_halt();

/**
 * Resets the computer.
 */
extern "C" void e_System_reset();

struct e_System* e_System_get() {
    return NULL;
}

void e_System_stop(struct e_System* system, enum e_System_Stop_Mode mode) {
    switch (mode) {
    case E_SYSTEM_HALT:
        // FIXME: implement halt shutdown mode
        e_Log_msg(e_Log_get(), E_LOG_WARN, "Halt shutdown not implemented.");
        eon::i386::support::finalize();
        e_System_halt();
        break;
    case E_SYSTEM_RESET:
        eon::i386::support::finalize();
        e_System_reset();
        break;
    default:
        e_Log_msg(e_Log_get(), E_LOG_ERROR, "Invalid system stop mode.");
        break;
    }
}
