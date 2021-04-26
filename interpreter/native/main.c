#include <stdlib.h>
#include "Log.h"

// Result data type experiment
// TODO: function name, file name, line number?
// TODO: define and describe error codes?
// TODO: compatible with `errno`

#include <errno.h>

#define K_RESULT(type) struct k_Result_##type

#define K_RESULT_OK(type, val) \
    (K_RESULT(type)) {.failed = false, .value = (val)}

#define K_RESULT_ERROR(type, code) \
    (K_RESULT(type)) {.failed = true, .error = (code)}

#define K_RESULT_DEFINE(type) \
    struct k_Result_##type { \
        bool failed; \
        union { \
            type value; \
            int error; \
        }; \
    }

K_RESULT_DEFINE(char);

K_RESULT(char) get_opt() {
    if (errno) {
        return K_RESULT_ERROR(char, EINVAL);
    }

    return K_RESULT_OK(char, '1');
}

int main(int argc, char* argv[]) {
    K_RESULT(char) result = get_opt();

    if (!result.failed) {
        char ch = result.value;
    }

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
