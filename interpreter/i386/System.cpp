/**
 * @see http://www.intel.com/products/processor/manuals/
 */

#include "../core/Log.h"
#include "../core/System.h"
#include "Multiboot.h"
#include "support.h"
#include "vga/Text.h"

/**
 * Interfaces the assembly and C++ source code.
 */
extern "C" void c_main() {
    eon::i386::support::initialize();
    e_VGA_Text_init();
    e_Multiboot_log_info(e_Multiboot_get_info(), e_Log_get());

    e_System* system = e_System_get();
    system->stop(system, E_SYSTEM_HALT);
}

/**
 * Halts the computer.
 */
extern "C" void e_System_halt();

/**
 * Resets the computer.
 */
extern "C" void e_System_reset();

static void stop(struct e_System* system, enum e_System_Stop_Mode mode) {
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

struct e_System* e_System_get() {
    static struct e_System system = {stop};
    return &system;
}
