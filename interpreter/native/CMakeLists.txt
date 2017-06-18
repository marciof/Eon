set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic-errors -Wall -Wextra")

add_executable(${PROJECT_NAME}.native
    ${core_sources}
    log.cpp
    memory.cpp
    system.cpp)
