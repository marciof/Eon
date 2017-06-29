enable_language(C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -pedantic-errors -Wall -Wextra -Wredundant-decls -Wshadow -Wswitch-default -Wundef -Wunused-macros -Wno-unused-parameter")

set(core_sources
    core/Log.c
    core/Log.h
    core/Memory.h
    core/System.h)

string(REGEX REPLACE "([^;]+)" "${CMAKE_CURRENT_SOURCE_DIR}/\\1"
    core_sources "${core_sources}")

add_subdirectory(native)
add_subdirectory(i386)
add_subdirectory(javascript)
