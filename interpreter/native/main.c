#include <stdlib.h>
#include "Log.h"

int main(int argc, char* argv[]) {
    struct k_Err err = K_ERR_INIT;
    struct k_Log log;

    k_Std_Stream_Log_init(&log);

    for (size_t i = 0; i < (unsigned) argc; ++i) {
        k_Log_info(&log, &err, "Command line: [{i}] '{s}'", i, argv[i]);

        if (k_Err_has(&err)) {
            k_Log_err_details(&log, &err);
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
