enable_language(C)

option(BUILD_FOR_NATIVE_HOST "Build the interpreter to run natively" ON)
option(BUILD_FOR_I386_HOST "Build the interpreter for an Intel x86 32-bit host" OFF)
option(BUILD_FOR_JAVASCRIPT_HOST "Build the interpreter for a JavaScript host" OFF)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -pedantic-errors -Wall -Wextra -Wredundant-decls -Wshadow -Wswitch-default -Wundef -Wunused-macros")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -pedantic-errors -Wall -Wreserved-id-macro -Wextra -Wshadow-all -Wundef -Wunused-macros -Wused-but-marked-unused")
endif()

set(CORE_SOURCES
    core/Ref.h
    core/Err.c
    core/Err.h
    core/Bit.h
    core/Log.c
    core/Log.h
    core/Memory.h)

# Build absolute paths for the core sources so that hosts that can't link
# directly against its library (eg. i386 cross-compiled from a amd64 machine)
# can instead reference each file directly.
string(REGEX REPLACE "([^;]+)" "${CMAKE_CURRENT_SOURCE_DIR}/\\1"
    CORE_SOURCES "${CORE_SOURCES}")

add_subdirectory(core)

if(BUILD_FOR_NATIVE_HOST)
    add_subdirectory(native)
endif()

if(BUILD_FOR_I386_HOST)
    add_subdirectory(i386)
endif()

if(BUILD_FOR_JAVASCRIPT_HOST)
    add_subdirectory(javascript)
endif()
