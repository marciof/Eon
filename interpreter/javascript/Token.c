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
        size_t col,
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
    token->col = col;

    return REF_INIT(token, Token_free);
}

static struct Str* Token_read_comment(struct Input* input, bool* has_err) {
    input->read(input, false, has_err); // Discard.

    if (*has_err) {
        return NULL;
    }

    struct Str* str = Str_new(has_err);

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

    return str;
}

static struct Str* Token_read_whitespace(struct Input* input, bool* has_err) {
    struct Str* str = Str_new(has_err);

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

    return str;
}

struct Token* Token_parse(struct Input* input, bool* has_err) {
    while (true) {
        int ch = input->read(input, true, has_err);

        if (*has_err || ch == EOF) {
            return NULL;
        }

        struct Str* str;
        enum Token_Type type;
        size_t line = input->line;
        size_t col = input->col;

        if (ch == COMMENT_QUOTE) {
            str = Token_read_comment(input, has_err);
            type = TOKEN_COMMENT;
        }
        else if ((ch == SPACE) || (ch == END_OF_LINE)) {
            str = Token_read_whitespace(input, has_err);
            type = TOKEN_WHITESPACE;
        }
        else {
            *has_err = true;
            ERR_PRINTF("Unexpected token '%c' at %s:%zu:%zu",
                (char) ch, input->location, input->line, input->col);
            return NULL;
        }

        struct Token* token = Token_new(type, str, input, line, col, has_err);
        REF_DEC(str);
        return token;
    }
}
