#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "../core/Bit.h"
#include "../core/Log.h"
#include "System.h"

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
