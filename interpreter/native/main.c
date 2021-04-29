#include <stdlib.h>
#include "Log.h"

// Result data type experiment
// TODO function name, file name, line number?
// TODO define and describe error codes?
// TODO compatible with `errno`
// TODO error prone to multiple evaluations, use inline-able function instead?

#include <errno.h>

#define K_RESULT(type) struct k_Result_##type

#define K_RESULT_OK(type, val) \
    (K_RESULT(type)) {.failed = false, .result.value = (val)}

#define K_RESULT_ERROR(type, code) \
    (K_RESULT(type)) {.failed = true, .result.error = (code)}

#define K_RESULT_FAILED(result) \
    ((result).failed)

#define K_RESULT_VALUE(result) \
    ((result).result.value)

#define K_RESULT_ERROR_CODE(result) \
    ((result).result.error)

#define K_RESULT_DEFINE(type) \
    struct k_Result_##type { \
        bool failed; \
        union { \
            type value; \
            int error; \
        } result; \
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

    if (!K_RESULT_FAILED(result)) {
        char ch = K_RESULT_VALUE(result);
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
