/**
 * @see http://www.intel.com/products/processor/manuals/
 */

#include "Multiboot.h"
#include "vga/Log.h"

extern void k_Cpu_halt(void);
void main(void);

/**
 * Shutdown isn't currently implemented, and so it just halts the CPU.
 */
void main(void) {
    struct k_Err err = K_ERR_INIT;

    struct k_Log log;
    k_VGA_Log_init(&log);

    struct multiboot_info* multiboot_info = k_Multiboot_get_info(&log, &err);
    if (k_Err_has(&err)) {
        goto ERROR;
    }

    k_Multiboot_log_info(multiboot_info, &log, &err);
    if (k_Err_has(&err)) {
        goto ERROR;
    }

    goto EXIT;

    ERROR:
    k_Log_err_details(&log, &err);

    EXIT:
    k_Log_warning(&log, &err, "Halting (shutdown not implemented)");
    k_Cpu_halt();
}
