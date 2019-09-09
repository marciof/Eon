/**
 * @see http://www.intel.com/products/processor/manuals/
 */

#include "../core/Log.h"
#include "Multiboot.h"
#include "vga/Text.h"

extern void k_Cpu_halt(void);

void main(void) {
    struct k_Err err = K_ERR_INIT;
    k_VGA_Text_init();

    // FIXME: move logging and other dependencies somewhere else?
    struct multiboot_info* multiboot_info = k_Multiboot_get_info(&err);
    struct k_Log* log = k_Log_get();

    if (!k_Err_has(&err)) {
        k_Multiboot_log_info(multiboot_info, &err, log);
    }
    else {
        k_Log_error(log, &err);
    }

    // FIXME: implement shutdown
    struct k_Err log_err = K_ERR_INIT;
    k_Log_msg(log, &log_err, K_LOG_WARN, "Shutdown not implemented");

    if (k_Err_has(&log_err)) {
        k_Log_error(log, &log_err);
    }

    k_Cpu_halt();
}
