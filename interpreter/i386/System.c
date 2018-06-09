/** @see http://www.intel.com/products/processor/manuals/ */

#include "../core/Bit.h"
#include "../core/Log.h"
#include "../core/System.h"
#include "Multiboot.h"
#include "vga/Text.h"

void main(void) {
    struct k_Err err = K_ERR_NONE;
    k_VGA_Text_init();

    // FIXME: move logging and other dependencies to k_System_start()
    struct multiboot_info* multiboot_info = k_Multiboot_get_info(&err);

    if (!k_Err_has(&err)) {
        k_Multiboot_log_info(multiboot_info, &err, k_Log_get());
    }

    struct k_System* system = k_System_get();
    system->stop(system, &err, K_SYSTEM_HALT);
}

extern void k_System_halt(void);

extern void k_System_reset(void);

static void stop(
        K_BIT_ATTR_UNUSED(struct k_System* system),
        struct k_Err* err,
        enum k_System_Stop_Mode mode) {

    switch (mode) {
    case K_SYSTEM_HALT:
        // FIXME: implement halt shutdown mode
        k_Log_msg(k_Log_get(), err, K_LOG_WARN, "Halt shutdown not implemented.");
        if (k_Err_has(err)) {
            k_Err_describe(err);
        }
        k_System_halt();
        break;
    case K_SYSTEM_RESET:
        k_System_reset();
        break;
    default:
        k_Log_msg(k_Log_get(), err, K_LOG_ERROR, "Invalid system stop mode.");
        break;
    }
}

struct k_System* k_System_get(void) {
    static struct k_System system = {stop};
    return &system;
}
