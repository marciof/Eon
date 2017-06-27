#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "Token.h"

static void e_Token_free(void* ptr) {
    struct e_Token* token = ptr;
    E_REF_DEC(token->str);
    E_REF_DEC(token->input);
    free(ptr);
}

static struct e_Token* e_Token_new(
        enum e_Token_Type type,
        struct e_Str* str,
        struct e_Input* input,
        size_t line,
        size_t column,
        bool* has_err) {

    struct e_Token* token = malloc(sizeof(*token));

    if (token == NULL) {
        *has_err = true;
        E_ERR_ERRNO();
        return NULL;
    }

    token->type = type;
    token->str = E_REF_INC(str);
    token->input = E_REF_INC(input);
    token->line = line;
    token->column = column;

    return E_REF_INIT(token, e_Token_free);
}

static struct e_Str* e_Token_read_comment(
        struct e_Input* input, bool* has_err) {

    input->read_ch(input, false, has_err); // Discard.
    if (*has_err) {
        return NULL;
    }

    struct e_Str* str = e_Str_new(has_err);
    if (*has_err) {
        return NULL;
    }

    while (true) {
        int ch = input->read_ch(input, false, has_err);

        if (*has_err) {
            E_REF_DEC(str);
            return NULL;
        }
        if (ch == EOF) {
            break;
        }

        e_Str_add_char(str, (char) ch, has_err);

        if (*has_err) {
            E_REF_DEC(str);
            return NULL;
        }
        if (ch == E_END_OF_LINE) {
            break;
        }
    }

    return str;
}

static struct e_Str* e_Token_read_whitespace(
        struct e_Input* input, bool* has_err) {

    struct e_Str* str = e_Str_new(has_err);
    if (*has_err) {
        return NULL;
    }

    while (true) {
        int ch = input->read_ch(input, true, has_err);

        if (*has_err) {
            E_REF_DEC(str);
            return NULL;
        }
        if ((ch != E_SPACE) && (ch != E_END_OF_LINE)) {
            break;
        }

        input->read_ch(input, false, has_err); // Discard.
        e_Str_add_char(str, (char) ch, has_err);

        if (*has_err) {
            E_REF_DEC(str);
            return NULL;
        }
    }

    return str;
}

struct e_Token* e_Token_parse(struct e_Input* input, bool* has_err) {
    int ch = input->read_ch(input, true, has_err);

    if (*has_err || ch == EOF) {
        return NULL;
    }

    struct e_Str* str;
    enum e_Token_Type type;
    size_t line = input->line;
    size_t column = input->column;

    if (ch == E_COMMENT_QUOTE) {
        str = e_Token_read_comment(input, has_err);
        type = E_TOKEN_COMMENT;
    }
    else if ((ch == E_SPACE) || (ch == E_END_OF_LINE)) {
        str = e_Token_read_whitespace(input, has_err);
        type = E_TOKEN_WHITESPACE;
    }
    else {
        *has_err = true;
        E_ERR_PRINTF("Unexpected token '%c' at %s:%zu:%zu",
            (char) ch, input->location, input->line, input->column);
        return NULL;
    }

    struct e_Token* token = e_Token_new(type, str, input, line, column, has_err);
    E_REF_DEC(str);
    return token;
}
