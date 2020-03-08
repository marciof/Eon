enable_language(C)

option(BUILD_FOR_NATIVE_HOST "Build the interpreter to run natively" ON)
option(BUILD_FOR_X86_32_HOST "Build the interpreter for an Intel x86 32-bit host" OFF)
option(BUILD_FOR_JAVASCRIPT_HOST "Build the interpreter for a JavaScript host" OFF)

include(CMakeDependentOption)
include(CheckCXXCompilerFlag)

cmake_dependent_option(
    BUILD_FOR_JAVASCRIPT_HOST "JavaScript host requires native host" ON
    "BUILD_FOR_NATIVE_HOST" OFF)

set(COMMON_GNU_CLANG_C_FLAGS "-std=c99 -pedantic-errors -Wall -Wextra -Wundef -Wunused-macros -Wvla -Wempty-body -Wdouble-promotion -Wformat=2 -Wc++-compat")

if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMMON_GNU_CLANG_C_FLAGS} -Wredundant-decls -Wshadow -Wswitch-default -Wlogical-op -Wjump-misses-init")

    foreach(FLAG "-Wduplicated-branches" "-Wrestrict" "-Wduplicated-cond" "-Wnull-dereference")
        check_cxx_compiler_flag("${FLAG}" IS_FLAG_SUPPORTED)

        if(IS_FLAG_SUPPORTED)
            set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${FLAG}")
        endif()
    endforeach(FLAG)
elseif(CMAKE_C_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMMON_GNU_CLANG_C_FLAGS} -Wreserved-id-macro -Wshadow-all -Wused-but-marked-unused -Wmissing-field-initializers -Wmissing-prototypes -Wsign-conversion")
endif()

if(CMAKE_C_COMPILER_ID MATCHES "^(GNU|Clang)$")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -z noexecstack")
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

if(BUILD_FOR_NATIVE_HOST)
    set(NATIVE_LIBRARY_NAME ${PROJECT_NAME}-native)
    add_subdirectory(native)
endif()

if(BUILD_FOR_X86_32_HOST)
    add_subdirectory(x86-32)
endif()

if(BUILD_FOR_JAVASCRIPT_HOST)
    add_subdirectory(javascript)
endif()
