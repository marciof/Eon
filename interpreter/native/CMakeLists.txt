add_library(${PROJECT_NAME}-native
    Log.c
    Memory.c
    System.c
    System.h)

add_executable(${PROJECT_NAME}
    main.c)

target_link_libraries(${PROJECT_NAME}
    ${PROJECT_NAME}-core
    ${PROJECT_NAME}-native)
