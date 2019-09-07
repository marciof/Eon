/** @see http://www.intel.com/products/processor/manuals/ */

#include "../core/Bit.h"
#include "../core/Log.h"
#include "Multiboot.h"
#include "vga/Text.h"

extern void k_Cpu_halt(void);

void main(void) {
    struct k_Err err = K_ERR_INIT;
    k_VGA_Text_init();

    // FIXME: move logging and other dependencies somewhere else?
    struct multiboot_info* multiboot_info = k_Multiboot_get_info(&err);

    if (!k_Err_has(&err)) {
        k_Multiboot_log_info(multiboot_info, &err, k_Log_get());
    }
    else {
        k_Err_describe(&err);
    }

    // FIXME: implement shutdown
    k_Err_reset(&err);
    k_Log_msg(k_Log_get(), &err, K_LOG_WARN, "Shutdown not implemented");

    if (k_Err_has(&err)) {
        k_Err_describe(&err);
    }

    k_Cpu_halt();
}
