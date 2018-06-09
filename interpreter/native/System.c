#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "../core/Bit.h"
#include "../core/Log.h"
#include "System.h"

static void reset(
        K_BIT_UNUSED(struct k_System* system),
        struct k_Err* err) {

    if (k_Err_has(err)) {
        k_Err_describe(err);
        k_Err_reset(err);
    }

    struct Native_System* native_system = (struct Native_System*) system->val;

    // FIXME: use Err/Errno
    if (execvp(native_system->argv[0], native_system->argv) != 0) {
        k_Log_msg(k_Log_get(), err, K_LOG_ERROR,
            "System reset error: errno={i}", errno);

        if (k_Err_has(err)) {
            k_Err_describe(err);
        }
    }
}

static void stop(
        K_BIT_UNUSED(struct k_System* system),
        struct k_Err* err) {

    if (k_Err_has(err)) {
        k_Err_describe(err);
    }

    exit(EXIT_SUCCESS);
}

struct k_System* k_System_get(void) {
    static uint8_t data_area[sizeof(struct k_Log) + sizeof(struct Native_System)];
    static struct k_System* system = NULL;

    if (system == NULL) {
        system = (struct k_System*) data_area;
        system->reset = reset;
        system->stop = stop;
    }

    return system;
}
