enable_language(CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ansi -pedantic-errors -Wall -Wextra -Weffc++ -Wold-style-cast -Wredundant-decls -Wshadow -Wswitch-default -Wundef -Wunused-macros -Wno-unused-parameter")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_CXX_FLAGS}")
string(REPLACE "-Weffc++ -Wold-style-cast" ""
    CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")

set(core_sources
    core/log.cpp
    core/log.h
    core/memory.cpp
    core/memory.h
    core/system.cpp
    core/system.h
    core/util.h)

string(REGEX REPLACE "([^;]+)" "${CMAKE_CURRENT_SOURCE_DIR}/\\1"
    core_sources "${core_sources}")

add_subdirectory(native)
add_subdirectory(x86)
add_subdirectory(scheme)
