enable_language(C)

if(CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -pedantic-errors -Wall -Wextra -Wredundant-decls -Wshadow -Wswitch-default -Wundef -Wunused-macros")
endif()

set(CORE_SOURCES
    core/Log.c
    core/Log.h
    core/Memory.h
    core/System.h)

# FIXME: build library instead of hardcoding direct paths to it
string(REGEX REPLACE "([^;]+)" "${CMAKE_CURRENT_SOURCE_DIR}/\\1"
    CORE_SOURCES "${CORE_SOURCES}")

add_subdirectory(native)
add_subdirectory(i386)
add_subdirectory(javascript)
