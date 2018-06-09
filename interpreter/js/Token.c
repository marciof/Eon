#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../core/Log.h"
#include "Token.h"

static void describe_token_err(struct k_Err* err) {
    struct k_Err discard_log_err = K_ERR_INIT;
    struct k_Input* input = (struct k_Input*) err->arg;
    int ch = input->peek_ch(input, &discard_log_err);

    // FIXME: avoid direct use of the singleton
    k_Log_msg(k_Log_get(), &discard_log_err, K_LOG_ERROR,
        "Unexpected token '{c}' at {s}:{iu}:{iu}",
        (char) ch, input->location, input->line, input->column);
}

static void free_token(void* ptr) {
    struct k_Token* token = ptr;
    K_REF_DEC(token->str);
    K_REF_DEC(token->input);
    free(ptr);
}

static struct k_Token* new_token(
        enum k_Token_Type type,
        struct k_Str* str,
        struct k_Input* input,
        size_t line,
        size_t column,
        struct k_Err* err) {

    struct k_Token* token = malloc(sizeof(*token));

    if (token == NULL) {
        K_ERR_SET_ERRNO(err, errno);
        return NULL;
    }

    token->type = type;
    token->str = K_REF_INC(str);
    token->input = K_REF_INC(input);
    token->line = line;
    token->column = column;

    return K_REF_INIT(token, free_token);
}

static struct k_Str* read_comment(struct k_Input* input, struct k_Err* err) {
    input->read_ch(input, err);
    if (k_Err_has(err)) {
        return NULL;
    }

    struct k_Str* str = k_Str_new(err);
    if (k_Err_has(err)) {
        return NULL;
    }

    while (true) {
        int ch = input->read_ch(input, err);

        if (k_Err_has(err)) {
            K_REF_DEC(str);
            return NULL;
        }
        if (ch == EOF) {
            break;
        }

        k_Str_add_char(str, (char) ch, err);

        if (k_Err_has(err)) {
            K_REF_DEC(str);
            return NULL;
        }
        if (ch == K_END_OF_LINE) {
            break;
        }
    }

    return str;
}

static struct k_Str* read_whitespace(struct k_Input* input, struct k_Err* err) {
    struct k_Str* str = k_Str_new(err);
    if (k_Err_has(err)) {
        return NULL;
    }

    while (true) {
        int ch = input->peek_ch(input, err);

        if (k_Err_has(err)) {
            K_REF_DEC(str);
            return NULL;
        }
        if ((ch != K_SPACE) && (ch != K_END_OF_LINE)) {
            break;
        }

        input->read_ch(input, err);
        k_Str_add_char(str, (char) ch, err);

        if (k_Err_has(err)) {
            K_REF_DEC(str);
            return NULL;
        }
    }

    return str;
}

struct k_Token* k_Token_parse(struct k_Input* input, struct k_Err* err) {
    int ch = input->peek_ch(input, err);

    if ((ch == EOF) || k_Err_has(err)) {
        return NULL;
    }

    struct k_Str* str;
    enum k_Token_Type type;
    size_t line = input->line;
    size_t column = input->column;

    if (ch == K_COMMENT_QUOTE) {
        str = read_comment(input, err);
        type = K_TOKEN_COMMENT;
    }
    else if ((ch == K_SPACE) || (ch == K_END_OF_LINE)) {
        str = read_whitespace(input, err);
        type = K_TOKEN_WHITESPACE;
    }
    else {
        K_ERR_SET(err, describe_token_err, input);
        return NULL;
    }

    struct k_Token* token = new_token(type, str, input, line, column, err);
    K_REF_DEC(str);
    return token;
}
