if(CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -pedantic-errors -Wall -Wextra")
endif()

add_executable(${PROJECT_NAME}.js
    main.c
    eon/Ref.h
    eon/Any.h
    eon/Any.c
    eon/Err.h
    eon/Str.h
    eon/Str.c
    eon/Token.h
    eon/Token.c
    eon/Input.h
    eon/Input.c)
