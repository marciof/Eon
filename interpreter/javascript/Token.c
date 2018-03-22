#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "Token.h"

static void Token_free(void* ptr) {
    struct k_Token* token = ptr;
    K_REF_DEC(token->str);
    K_REF_DEC(token->input);
    free(ptr);
}

static struct k_Token* Token_new(
        enum k_Token_Type type,
        struct k_Str* str,
        struct k_Input* input,
        size_t line,
        size_t column,
        bool* has_err) {

    struct k_Token* token = malloc(sizeof(*token));

    if (token == NULL) {
        *has_err = true;
        K_ERR_ERRNO();
        return NULL;
    }

    token->type = type;
    token->str = K_REF_INC(str);
    token->input = K_REF_INC(input);
    token->line = line;
    token->column = column;

    return K_REF_INIT(token, Token_free);
}

static struct k_Str* read_comment(struct k_Input* input, bool* has_err) {
    input->read_ch(input, has_err);
    if (*has_err) {
        return NULL;
    }

    struct k_Str* str = k_Str_new(has_err);
    if (*has_err) {
        return NULL;
    }

    while (true) {
        int ch = input->read_ch(input, has_err);

        if (*has_err) {
            K_REF_DEC(str);
            return NULL;
        }
        if (ch == EOF) {
            break;
        }

        k_Str_add_char(str, (char) ch, has_err);

        if (*has_err) {
            K_REF_DEC(str);
            return NULL;
        }
        if (ch == K_END_OF_LINE) {
            break;
        }
    }

    return str;
}

static struct k_Str* read_whitespace(struct k_Input* input, bool* has_err) {
    struct k_Str* str = k_Str_new(has_err);
    if (*has_err) {
        return NULL;
    }

    while (true) {
        int ch = input->peek_ch(input, has_err);

        if (*has_err) {
            K_REF_DEC(str);
            return NULL;
        }
        if ((ch != K_SPACE) && (ch != K_END_OF_LINE)) {
            break;
        }

        input->read_ch(input, has_err);
        k_Str_add_char(str, (char) ch, has_err);

        if (*has_err) {
            K_REF_DEC(str);
            return NULL;
        }
    }

    return str;
}

struct k_Token* k_Token_parse(struct k_Input* input, bool* has_err) {
    int ch = input->peek_ch(input, has_err);

    if (*has_err || ch == EOF) {
        return NULL;
    }

    struct k_Str* str;
    enum k_Token_Type type;
    size_t line = input->line;
    size_t column = input->column;

    if (ch == K_COMMENT_QUOTE) {
        str = read_comment(input, has_err);
        type = K_TOKEN_COMMENT;
    }
    else if ((ch == K_SPACE) || (ch == K_END_OF_LINE)) {
        str = read_whitespace(input, has_err);
        type = K_TOKEN_WHITESPACE;
    }
    else {
        *has_err = true;
        K_ERR_PRINTF("Unexpected token '%c' at %s:%zu:%zu",
            (char) ch, input->location, input->line, input->column);
        return NULL;
    }

    struct k_Token* token = Token_new(type, str, input, line, column, has_err);
    K_REF_DEC(str);
    return token;
}
