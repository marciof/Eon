/**
 * Wrapper over `<time.h>` to include definitions that may be missing in some
 * environments.
 */

#pragma once
#include <time.h>

/**
 * @see https://docs.microsoft.com/cpp/preprocessor/predefined-macros
 */
#ifdef _MSC_VER
#include <errno.h>

struct tm* gmtime_r(const time_t* timep, struct tm* result) {
    errno = gmtime_s(result, timep);
    return result;
}
#endif
