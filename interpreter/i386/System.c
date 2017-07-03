/**
 * @see http://www.intel.com/products/processor/manuals/
 */

#include "../core/Log.h"
#include "../core/System.h"
#include "Multiboot.h"
#include "vga/Text.h"

void main() {
    e_VGA_Text_init();
    e_Multiboot_log_info(e_Multiboot_get_info(), e_Log_get());

    struct e_System* system = e_System_get();
    system->stop(system, E_SYSTEM_HALT);
}

extern void e_System_halt();

extern void e_System_reset();

static void stop(struct e_System* system, enum e_System_Stop_Mode mode) {
    switch (mode) {
    case E_SYSTEM_HALT:
        // FIXME: implement halt shutdown mode
        e_Log_msg(e_Log_get(), E_LOG_WARN, "Halt shutdown not implemented.");
        e_System_halt();
        break;
    case E_SYSTEM_RESET:
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
