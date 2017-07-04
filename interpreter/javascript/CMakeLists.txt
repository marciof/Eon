# FIXME: merge into core
add_executable(${PROJECT_NAME}.js
    main.c
    Ref.h
    Err.h
    Str.h
    Str.c
    Token.h
    Token.c
    Input.h
    Input.c)

target_link_libraries(${PROJECT_NAME}.js ${PROJECT_NAME})
