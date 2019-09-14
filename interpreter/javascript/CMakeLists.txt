set(EXECUTABLE_NAME_JAVASCRIPT ${PROJECT_NAME}-javascript)

add_executable(${EXECUTABLE_NAME_JAVASCRIPT}
    main.c
    Str.h
    Str.c
    Token.h
    Token.c
    Input.h
    Input.c)

target_link_libraries(${EXECUTABLE_NAME_JAVASCRIPT}
    ${CORE_LIBRARY_NAME}
    ${NATIVE_LIBRARY_NAME})
