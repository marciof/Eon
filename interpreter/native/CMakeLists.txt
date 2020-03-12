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

option(BUILD_NATIVE_WITH_ASAN "Enable Address Sanitizer" OFF)

# Address Sanitizer
# https://github.com/google/sanitizers/wiki/AddressSanitizer
# https://github.com/google/sanitizers/wiki/AddressSanitizerFlags
if(BUILD_NATIVE_WITH_ASAN AND (CMAKE_C_COMPILER_ID MATCHES "^(GNU|Clang)$"))
    set(ADDRESS_SANITIZER_FLAGS "-fsanitize=address" "-fno-omit-frame-pointer")

    target_compile_options(${EXECUTABLE_NAME_NATIVE} PUBLIC ${ADDRESS_SANITIZER_FLAGS})
    target_compile_options(${NATIVE_LIBRARY_NAME} PUBLIC ${ADDRESS_SANITIZER_FLAGS})

    target_link_libraries(${EXECUTABLE_NAME_NATIVE} ${ADDRESS_SANITIZER_FLAGS})
    target_link_libraries(${NATIVE_LIBRARY_NAME} ${ADDRESS_SANITIZER_FLAGS})
endif()
