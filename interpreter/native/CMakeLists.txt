# POSIX.1-2017, Compilation Environment, _POSIX_C_SOURCE Feature Test Macro
# https://pubs.opengroup.org/onlinepubs/9699919799/functions/V2_chap02.html#tag_15_02_01_01
add_definitions(-D_POSIX_C_SOURCE=200809L)

add_library(${PROJECT_NAME}-native
    Log.h
    Log.c
    Errno.c
    Errno.h
    Memory.c)

add_executable(${PROJECT_NAME}
    main.c)

target_link_libraries(${PROJECT_NAME}
    ${PROJECT_NAME}-core
    ${PROJECT_NAME}-native)
