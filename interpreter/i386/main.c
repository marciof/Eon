/**
 * @see http://www.intel.com/products/processor/manuals/
 */

#include "../core/Log.h"
#include "Multiboot.h"
#include "vga/Text.h"

extern void k_Cpu_halt(void);

void main(void) {
    k_VGA_Text_init();

    // FIXME: move logging and other dependencies somewhere else?
    struct k_Log* log = k_Log_get();
    struct k_Err err = K_ERR_INIT;

    struct multiboot_info* multiboot_info = k_Multiboot_get_info(log, &err);
    if (k_Err_has(&err)) {
        goto ERROR;
    }

    k_Multiboot_log_info(multiboot_info, log, &err);
    if (k_Err_has(&err)) {
        goto ERROR;
    }

    goto EXIT;

    ERROR:
    k_Log_error(log, &err);

    EXIT:
    k_Log_msg(log, &err, K_LOG_WARN, "Shutdown not implemented");
    // FIXME: implement shutdown
    k_Cpu_halt();
}
