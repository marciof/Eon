if(CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -pedantic-errors -Wall -Wextra")
endif()

add_executable(${PROJECT_NAME}.js
    main.c
    eon/ref.h
    eon/any.h
    eon/any.c
    eon/err.h
    eon/str.h
    eon/str.c
    eon/token.h
    eon/token.c
    eon/input.h
    eon/input.c)
