#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "Token.h"

#define COMMENT_QUOTE 0x23
#define END_OF_LINE 0xA
#define SPACE 0x20

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

static struct Token* Token_read_comment(struct Input* input, bool* has_err) {
    input->read(input->arg, false, has_err); // Discard.

    if (*has_err) {
        return NULL;
    }

    struct Str* str = Str_new(has_err);

    if (*has_err) {
        return NULL;
    }

    while (true) {
        int ch = input->read(input->arg, false, has_err);

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

    struct Token* token = Token_new(TOKEN_COMMENT, str, has_err);
    REF_DEC(str);
    return token;
}

static struct Token* Token_read_whitespace(struct Input* input, bool* has_err) {
    struct Str* str = Str_new(has_err);

    if (*has_err) {
        return NULL;
    }

    while (true) {
        int ch = input->read(input->arg, true, has_err);

        if (*has_err) {
            REF_DEC(str);
            return NULL;
        }
        if ((ch == EOF) || ((ch != SPACE) && (ch != END_OF_LINE))) {
            break;
        }

        input->read(input->arg, false, has_err); // Discard.
        Str_append_char(str, (char) ch, has_err);

        if (*has_err) {
            REF_DEC(str);
            return NULL;
        }
    }

    struct Token* token = Token_new(TOKEN_WHITESPACE, str, has_err);
    REF_DEC(str);
    return token;
}

struct Token* Token_read(struct Input* input, bool* has_err) {
    while (true) {
        int ch = input->read(input->arg, true, has_err);

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
                ERR_PRINTF("Unexpected token '%c' at %s:%d:%d",
                    (char) ch, input->location, 0, 0);
                return NULL;
        }
    }
}
