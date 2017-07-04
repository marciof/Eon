add_executable(${PROJECT_NAME}.native
    Log.c
    Memory.c
    System.c)

target_link_libraries(${PROJECT_NAME}.native ${PROJECT_NAME})
