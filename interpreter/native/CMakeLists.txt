add_library(${PROJECT_NAME}-native
    Log.h
    Log.c
    Memory.c)

add_executable(${PROJECT_NAME}
    main.c)

target_link_libraries(${PROJECT_NAME}
    ${PROJECT_NAME}-core
    ${PROJECT_NAME}-native)
