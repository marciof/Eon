#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "../core/Bit.h"
#include "../core/Log.h"
#include "../core/System.h"

struct Native_System {
    size_t argc;
    char** argv;
};

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

struct k_System* k_System_get() {
    static uint8_t data_area[sizeof(struct k_Log) + sizeof(struct Native_System)];
    static struct k_System* system = NULL;

    if (system == NULL) {
        system = (struct k_System*) data_area;
        system->stop = stop;
    }

    return system;
}

int main(int argc, char* argv[]) {
    struct k_System* system = k_System_get();

    // FIXME: move to initialization once Log and System are decoupled via Err
    struct Native_System* native_system = (struct Native_System*) system->val;
    native_system->argc = (unsigned) argc;
    native_system->argv = argv;

    // FIXME: log full command line
    // FIXME: move logging to k_System_start()
    k_Log_msg(k_Log_get(), K_LOG_INFO, "Command line: count={i}", argc);

    system->stop(system, K_SYSTEM_HALT);
    return EXIT_FAILURE;
}
