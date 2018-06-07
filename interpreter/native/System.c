#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "../core/Bit.h"
#include "../core/Log.h"
#include "System.h"

static void stop(
        K_BIT_ATTR_UNUSED(struct k_System* system),
        enum k_System_Stop_Mode mode) {

    struct Native_System* native_system = (struct Native_System*) system->val;

    switch (mode) {
    case K_SYSTEM_HALT:
        exit(EXIT_SUCCESS);
    case K_SYSTEM_RESET:
        if (execvp(native_system->argv[0], native_system->argv) != 0) {
            k_Log_msg(k_Log_get(), K_LOG_ERROR,
                "System reset error: errno={i}", errno);
        }
        break;
    default:
        k_Log_msg(k_Log_get(), K_LOG_ERROR, "Invalid system stop mode.");
        break;
    }
}

struct k_System* k_System_get(void) {
    static uint8_t data_area[sizeof(struct k_Log) + sizeof(struct Native_System)];
    static struct k_System* system = NULL;

    if (system == NULL) {
        system = (struct k_System*) data_area;
        system->stop = stop;
    }

    return system;
}
