set(EXECUTABLE_NAME_NATIVE ${PROJECT_NAME})

# POSIX.1-2017, Compilation Environment, _POSIX_C_SOURCE Feature Test Macro
# https://pubs.opengroup.org/onlinepubs/9699919799/functions/V2_chap02.html#tag_15_02_01_01
add_definitions(-D_POSIX_C_SOURCE=200809L)

add_library(${NATIVE_LIBRARY_NAME}
    Log.h
    Log.c
    Errno.c
    Errno.h)

add_executable(${EXECUTABLE_NAME_NATIVE}
    main.c)

target_link_libraries(${EXECUTABLE_NAME_NATIVE}
    ${CORE_LIBRARY_NAME}
    ${NATIVE_LIBRARY_NAME})
