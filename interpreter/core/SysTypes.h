/**
 * Wrapper over `sys/types.h` to include types that may be missing in some
 * environments.
 */

#pragma once
#include <sys/types.h>

/**
 * @see https://docs.microsoft.com/cpp/preprocessor/predefined-macros
 */
#ifdef _MSC_VER
#include <BaseTsd.h>
/**
 * @see https://docs.microsoft.com/windows/win32/winprog/windows-data-types#SSIZE_T
 */
typedef SSIZE_T ssize_t;
#endif
