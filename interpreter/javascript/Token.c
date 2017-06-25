#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "Token.h"

static void Token_free(void* ptr) {
    struct Token* token = ptr;
    REF_DEC(token->str);
    REF_DEC(token->input);
    free(ptr);
}

static struct Token* Token_new(
        enum Token_Type type,
        struct Str* str,
        struct Input* input,
        size_t line,
        size_t column,
        bool* has_err) {

    struct Token* token = malloc(sizeof(*token));

    if (token == NULL) {
        *has_err = true;
        ERR_PRINT_ERRNO();
        return NULL;
    }

    token->type = type;
    token->str = REF_INC(str);
    token->input = REF_INC(input);
    token->line = line;
    token->column = column;

    return REF_INIT(token, Token_free);
}

static struct Token* Token_read_comment(struct Input* input, bool* has_err) {
    input->read(input, false, has_err); // Discard.

    if (*has_err) {
        return NULL;
    }

    struct Str* str = Str_new(has_err);
    size_t line = input->line;
    size_t column = input->column;

    if (*has_err) {
        return NULL;
    }

    while (true) {
        int ch = input->read(input, false, has_err);

        if (*has_err) {
            REF_DEC(str);
            return NULL;
        }
        if (ch == EOF) {
            break;
        }

        Str_append_char(str, (char) ch, has_err);

        if (*has_err) {
            REF_DEC(str);
            return NULL;
        }
        if (ch == END_OF_LINE) {
            break;
        }
    }

    struct Token* token = Token_new(
        TOKEN_COMMENT, str, input, line, column, has_err);
    REF_DEC(str);
    return token;
}

static struct Token* Token_read_whitespace(struct Input* input, bool* has_err) {
    struct Str* str = Str_new(has_err);
    size_t line = input->line;
    size_t column = input->column;

    if (*has_err) {
        return NULL;
    }

    while (true) {
        int ch = input->read(input, true, has_err);

        if (*has_err) {
            REF_DEC(str);
            return NULL;
        }
        if ((ch != SPACE) && (ch != END_OF_LINE)) {
            break;
        }

        input->read(input, false, has_err); // Discard.
        Str_append_char(str, (char) ch, has_err);

        if (*has_err) {
            REF_DEC(str);
            return NULL;
        }
    }

    struct Token* token = Token_new(
        TOKEN_WHITESPACE, str, input, line, column, has_err);
    REF_DEC(str);
    return token;
}

struct Token* Token_read(struct Input* input, bool* has_err) {
    while (true) {
        int ch = input->read(input, true, has_err);

        if (*has_err || ch == EOF) {
            return NULL;
        }

        switch (ch) {
            case COMMENT_QUOTE:
                return Token_read_comment(input, has_err);
            case SPACE:
            case END_OF_LINE:
                return Token_read_whitespace(input, has_err);
            default:
                *has_err = true;
                ERR_PRINTF("Unexpected token '%c' at %s:%zu:%zu",
                    (char) ch, input->location, input->line, input->column);
                return NULL;
        }
    }
}
