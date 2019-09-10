# FIXME: merge into core
add_executable(${PROJECT_NAME}-javascript
    main.c
    Str.h
    Str.c
    Token.h
    Token.c
    Input.h
    Input.c)

target_link_libraries(${PROJECT_NAME}-javascript
    ${PROJECT_NAME}-core
    ${PROJECT_NAME}-native)
