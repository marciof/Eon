#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "../core/Bit.h"
#include "../core/Log.h"
#include "../core/System.h"

// FIXME: don't make argv global state
static char** _argv = NULL;

static void stop(
        K_BIT_ATTR_UNUSED(struct k_System* system),
        enum k_System_Stop_Mode mode) {

    switch (mode) {
    case K_SYSTEM_HALT:
        exit(EXIT_SUCCESS);
    case K_SYSTEM_RESET:
        if (execvp(_argv[0], _argv) != 0) {
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
    static struct k_System system = {stop};
    return &system;
}

int main(K_BIT_ATTR_UNUSED(int argc), char* argv[]) {
    _argv = argv;
    struct k_System* system = k_System_get();
    system->stop(system, K_SYSTEM_HALT);
    return EXIT_FAILURE;
}
