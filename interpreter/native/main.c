#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "../core/Bit.h"
#include "../core/Log.h"

int main(int argc, char* argv[]) {
    struct k_Err err = K_ERR_INIT;
    struct k_Log* log = k_Log_get();

    // FIXME: log full command line
    // FIXME: move logging elsewhere?
    for (size_t i = 0; i < (unsigned) argc; ++i) {
        k_Log_msg(log, &err, K_LOG_INFO,
            "Command line: [{i}] '{s}'", i, argv[i]);

        if (k_Err_has(&err)) {
            k_Log_err(log, &err);
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
