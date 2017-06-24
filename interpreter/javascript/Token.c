#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "Token.h"

struct Token_Match {
    bool is_match;
    bool want_more;
    ssize_t line_delta;
    ssize_t column_delta;
};

static struct Token_Match match_whitespace(char ch) {
    switch (ch) {
        case 0x20:
            return (struct Token_Match) {true, true, 0, +1};
        case 0xA:
            return (struct Token_Match) {true, true, +1, 0};
        default:
            return (struct Token_Match) {false, false, 0, 0};
    }
}

static void Token_free(void* token) {
    REF_DEC(((struct Token*) token)->str);
    free(token);
}

static struct Token* Token_new(
        enum Token_Type type, struct Str* str, bool* has_err) {

    struct Token* token = malloc(sizeof(*token));

    if (token == NULL) {
        *has_err = true;
        ERR_PRINT_ERRNO();
        return NULL;
    }

    token->type = type;
    token->str = REF_INC(str);
    return REF_INIT(token, Token_free);
}

struct Token* Token_read(struct Input* input, bool* has_err) {
    struct Str* str = NULL;
    size_t line = 1;
    size_t column = 1;

    while (true) {
        struct Str* buffer = input->read(input->arg, has_err);

        if (*has_err) {
            REF_DEC(str);
            ERR_PRINT("Input read error");
            return NULL;
        }
        if (buffer == NULL) {
            break;
        }

        for (size_t i = 0; i < buffer->len; ++i) {
            char ch = buffer->val[i];
            struct Token_Match match = match_whitespace(ch);

            if (match.is_match) {
                line += match.line_delta;
                column += match.column_delta;
                continue;
            }

            *has_err = true;
            REF_DEC(str);
            REF_DEC(buffer);
            ERR_PRINTF("Unexpected char '%c' at %s:%zu:%zu",
                ch, input->location, line, column);
            return NULL;
        }

        if (str == NULL) {
            str = buffer;
            continue;
        }

        Str_append(str, buffer, has_err);
        REF_DEC(buffer);

        if (*has_err) {
            REF_DEC(str);
            return NULL;
        }
    }

    if (str == NULL) {
        return NULL;
    }

    struct Token* token = Token_new(WHITE_SPACE, str, has_err);
    REF_DEC(str);

    if (*has_err) {
        return NULL;
    }

    return token;
}
