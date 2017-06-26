if(CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -pedantic-errors -Wall -Wextra")
endif()

add_executable(${PROJECT_NAME}.js
    main.c
    Ref.h
    Any.h
    Any.c
    Err.h
    Str.h
    Str.c
    Token.h
    Token.c
    Input.h
    Input.c)
