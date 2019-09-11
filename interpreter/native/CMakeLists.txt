# https://www.gnu.org/software/libc/manual/html_node/Feature-Test-Macros.html
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
