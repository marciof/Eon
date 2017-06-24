#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Any.h"
#include "Err.h"
#include "Str.h"

enum Token_Type {
    WHITE_SPACE
};

struct Token {
    enum Token_Type type;
    struct Str* val;
    REF_FIELDS;
};

struct Token_Match {
    bool is_match;
    ssize_t line_delta;
    ssize_t column_delta;
};

struct Input {
    union Any arg;
    char* location;
    struct Str* (*read)(union Any arg, bool* has_err);
};

struct Token_Match match_whitespace(char ch) {
    switch (ch) {
        case 0x20:
            return (struct Token_Match) {true, 0, +1};
        case 0xA:
            return (struct Token_Match) {true, +1, 0};
        default:
            return (struct Token_Match) {false, 0, 0};
    }
}

struct Str* read_input_fd(union Any fd, bool* has_err) {
    char buffer[BUFSIZ];
    ssize_t len_bytes = read((int) fd.val, buffer, BUFSIZ * sizeof(*buffer));

    if (len_bytes == 0) {
        return NULL;
    }
    else if (len_bytes == -1) {
        *has_err = true;
        ERR_PRINT_ERRNO();
        return NULL;
    }

    return Str_from_chars(buffer, len_bytes / sizeof(*buffer), has_err);
}

struct Token* read_token(struct Input* input, bool* has_err) {
    struct Str* token = NULL;
    size_t line = 1;
    size_t column = 1;

    while (true) {
        struct Str* buffer = input->read(input->arg, has_err);

        if (*has_err) {
            REF_DEC(token);
            ERR_PRINT("Input read error");
            return NULL;
        }
        if (buffer == NULL) {
            break;
        }

        for (size_t i = 0; i < buffer->len; ++i) {
            char ch = buffer->val[i];
            struct Token_Match check = match_whitespace(ch);

            if (check.is_match) {
                line += check.line_delta;
                column += check.column_delta;
                continue;
            }

            *has_err = true;
            REF_DEC(token);
            REF_DEC(buffer);
            ERR_PRINTF("Unexpected char '%c' at %s:%zu:%zu", ch, input->location, line, column);
            return NULL;
        }

        if (token == NULL) {
            token = buffer;
            continue;
        }

        Str_append(token, buffer, has_err);
        REF_DEC(buffer);

        if (*has_err) {
            REF_DEC(token);
            return NULL;
        }
    }

    if (token != NULL) {
        printf("[%.*s]\n", (int) token->len, token->val);
        REF_DEC(token);
    }

    return NULL;
}

int main() {
    bool has_err = false;

    struct Input stdin_input = {
        Any_val(STDIN_FILENO),
        "<stdin>",
        read_input_fd,
    };

    read_token(&stdin_input, &has_err);
    return has_err ? EXIT_FAILURE : EXIT_SUCCESS;
}
