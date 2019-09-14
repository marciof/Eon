enable_language(C)

option(BUILD_FOR_NATIVE_HOST "Build the interpreter to run natively" ON)
option(BUILD_FOR_I386_HOST "Build the interpreter for an Intel x86 32-bit host" OFF)
option(BUILD_FOR_JAVASCRIPT_HOST "Build the interpreter for a JavaScript host" OFF)

include(CMakeDependentOption)
cmake_dependent_option(
    BUILD_FOR_JAVASCRIPT_HOST "JavaScript host requires native host" ON
    "BUILD_FOR_NATIVE_HOST" OFF)

if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -pedantic-errors -Wall -Wextra -Wredundant-decls -Wshadow -Wswitch-default -Wundef -Wunused-macros")
elseif(CMAKE_C_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -pedantic-errors -Wall -Wreserved-id-macro -Wextra -Wshadow-all -Wundef -Wunused-macros -Wused-but-marked-unused -Wmissing-field-initializers -Wmissing-prototypes -Wsign-conversion")
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

set(CORE_LIBRARY_NAME ${PROJECT_NAME}-core)
add_subdirectory(core)

if(BUILD_FOR_NATIVE_HOST)
    set(NATIVE_LIBRARY_NAME ${PROJECT_NAME}-native)
    add_subdirectory(native)
endif()

if(BUILD_FOR_I386_HOST)
    add_subdirectory(i386)
endif()

if(BUILD_FOR_JAVASCRIPT_HOST)
    add_subdirectory(javascript)
endif()
