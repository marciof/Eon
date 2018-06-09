/** @see http://www.intel.com/products/processor/manuals/ */

#include "../core/Bit.h"
#include "../core/Log.h"
#include "../core/System.h"
#include "Multiboot.h"
#include "vga/Text.h"

extern void k_System_halt(void);
extern void k_System_reset(void);

void main(void) {
    struct k_Err err = K_ERR_INIT;
    k_VGA_Text_init();

    // FIXME: move logging and other dependencies to a k_System_start?
    struct multiboot_info* multiboot_info = k_Multiboot_get_info(&err);

    if (!k_Err_has(&err)) {
        k_Multiboot_log_info(multiboot_info, &err, k_Log_get());
    }

    struct k_System* system = k_System_get();
    system->stop(system, &err);
}

static void reset(
        K_BIT_UNUSED(struct k_System* system),
        K_BIT_UNUSED(struct k_Err* err)) {

    if (k_Err_has(err)) {
        k_Err_describe(err);
    }

    k_System_reset();
}

static void stop(
        K_BIT_UNUSED(struct k_System* system),
        struct k_Err* err) {

    if (k_Err_has(err)) {
        k_Err_describe(err);
        k_Err_reset(err);
    }

    // FIXME: implement shutdown
    k_Log_msg(k_Log_get(), err, K_LOG_WARN, "Shutdown not implemented");

    if (k_Err_has(err)) {
        k_Err_describe(err);
    }

    k_System_halt();
}

struct k_System* k_System_get(void) {
    static struct k_System system = {reset, stop};
    return &system;
}
