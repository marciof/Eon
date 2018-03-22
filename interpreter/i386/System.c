/**
 * @see http://www.intel.com/products/processor/manuals/
 */

#include "../core/Log.h"
#include "../core/System.h"
#include "Multiboot.h"
#include "vga/Text.h"

void main() {
    k_VGA_Text_init();
    k_Multiboot_log_info(k_Multiboot_get_info(), k_Log_get());

    struct k_System* system = k_System_get();
    system->stop(system, K_SYSTEM_HALT);
}

extern void k_System_halt();

extern void k_System_reset();

static void stop(struct k_System* system, enum k_System_Stop_Mode mode) {
    switch (mode) {
    case K_SYSTEM_HALT:
        // FIXME: implement halt shutdown mode
        k_Log_msg(k_Log_get(), K_LOG_WARN, "Halt shutdown not implemented.");
        k_System_halt();
        break;
    case K_SYSTEM_RESET:
        k_System_reset();
        break;
    default:
        k_Log_msg(k_Log_get(), K_LOG_ERROR, "Invalid system stop mode.");
        break;
    }
}

struct k_System* k_System_get() {
    static struct k_System system = {stop};
    return &system;
}
