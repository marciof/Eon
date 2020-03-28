enable_language(C)

include(CMakeDependentOption)
include(CheckCCompilerFlag)

option(BUILD_NATIVE "Build the interpreter to run natively" OFF)
option(BUILD_X86_32 "Build the interpreter for an Intel x86 32-bit host" OFF)
option(BUILD_JAVASCRIPT "Build the interpreter for a JavaScript host" OFF)

cmake_dependent_option(BUILD_JAVASCRIPT "JavaScript host requires native host" ON
    "BUILD_NATIVE_HOST" OFF)

if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -pedantic-errors -Wall -Wextra -Wundef -Wunused-macros -Wvla -Wempty-body -Wdouble-promotion -Wformat=2 -Wc++-compat -Wredundant-decls -Wshadow -Wswitch-default -Wlogical-op -Wjump-misses-init")

    check_c_compiler_flag("-Wduplicated-branches" COMPILER_SUPPORTS_DUP_BRANCHES)
    if(COMPILER_SUPPORTS_DUP_BRANCHES)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wduplicated-branches")
    endif()

    check_c_compiler_flag("-Wrestrict" COMPILER_SUPPORTS_RESTRICT)
    if(COMPILER_SUPPORTS_RESTRICT)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wrestrict")
    endif()

    check_c_compiler_flag("-Wduplicated-cond" COMPILER_SUPPORTS_DUP_COND)
    if(COMPILER_SUPPORTS_DUP_COND)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wduplicated-cond")
    endif()

    check_c_compiler_flag("-Wnull-dereference" COMPILER_SUPPORTS_NULL_DEREF)
    if(COMPILER_SUPPORTS_NULL_DEREF)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wnull-dereference")
    endif()
elseif(CMAKE_C_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -pedantic-errors -Wall -Wextra -Wundef -Wunused-macros -Wvla -Wempty-body -Wdouble-promotion -Wformat=2 -Wc++-compat -Wreserved-id-macro -Wshadow-all -Wused-but-marked-unused -Wmissing-field-initializers -Wmissing-prototypes -Wsign-conversion")
endif()

if(CMAKE_C_COMPILER_ID MATCHES "^(GNU|Clang)$")
    # Workaround for checking if a linker flag is supported.
    # https://cmake.org/pipermail/cmake/2011-July/045525.html
    # https://public.kitware.com/Bug/view.php?id=15934
    set(CMAKE_REQUIRED_FLAGS "-Wl,-z,noexecstack")
    check_c_compiler_flag("" LINKER_SUPPORTS_NO_EXEC_STACK)

    if(LINKER_SUPPORTS_NO_EXEC_STACK)
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -z noexecstack")
    endif()
endif()

set(CORE_SOURCES
    core/Ref.h
    core/Err.c
    core/Err.h
    core/Bit.h
    core/Log.c
    core/Log.h)

# Build absolute paths for the core sources so that hosts that can't link
# directly against its library (eg. 32-bit cross-compiled from a 64-bit machine)
# can instead reference each file directly.
string(REGEX REPLACE "([^;]+)" "${CMAKE_CURRENT_SOURCE_DIR}/\\1"
    CORE_SOURCES "${CORE_SOURCES}")

set(CORE_LIBRARY_NAME ${PROJECT_NAME}-core)
add_subdirectory(core)

if(BUILD_NATIVE)
    set(NATIVE_LIBRARY_NAME ${PROJECT_NAME}-native)
    add_subdirectory(native)
endif()

if(BUILD_X86_32)
    add_subdirectory(x86-32)
endif()

if(BUILD_JAVASCRIPT_HOST)
    add_subdirectory(javascript)
endif()
