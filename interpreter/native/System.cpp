#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "../core/System.h"
#include "../core/Log.h"

// FIXME: don't make argv global state
static char** _argv = NULL;

static void stop(struct e_System* system, enum e_System_Stop_Mode mode) {
    switch (mode) {
    case E_SYSTEM_HALT:
        exit(EXIT_SUCCESS);
    case E_SYSTEM_RESET:
        if (execvp(_argv[0], _argv) != 0) {
            e_Log_msg(e_Log_get(), E_LOG_ERROR,
                "System reset error: errno={i}", errno);
        }
        break;
    default:
        e_Log_msg(e_Log_get(), E_LOG_ERROR, "Invalid system stop mode.");
        break;
    }
}

struct e_System* e_System_get() {
    static struct e_System system = {stop};
    return &system;
}

int main(int argc, char* argv[]) {
    _argv = argv;
    e_System* system = e_System_get();
    system->stop(system, E_SYSTEM_HALT);
    return EXIT_FAILURE;
}
