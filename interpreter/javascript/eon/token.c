#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "token.h"

static void token_free(void* ptr) {
    struct eon_token* token = ptr;
    EON_REF_DEC(token->str);
    EON_REF_DEC(token->input);
    free(ptr);
}

static struct eon_token* token_new(
        enum eon_token_type type,
        struct eon_str* str,
        struct eon_input* input,
        size_t line,
        size_t col,
        bool* has_err) {

    struct eon_token* token = malloc(sizeof(*token));

    if (token == NULL) {
        *has_err = true;
        EON_ERR_ERRNO();
        return NULL;
    }

    token->type = type;
    token->str = EON_REF_INC(str);
    token->input = EON_REF_INC(input);
    token->line = line;
    token->col = col;

    return EON_REF_INIT(token, token_free);
}

static struct eon_str* token_read_comment(
        struct eon_input* input, bool* has_err) {

    input->read(input, false, has_err); // Discard.
    if (*has_err) {
        return NULL;
    }

    struct eon_str* str = eon_str_new(has_err);
    if (*has_err) {
        return NULL;
    }

    while (true) {
        int ch = input->read(input, false, has_err);

        if (*has_err) {
            EON_REF_DEC(str);
            return NULL;
        }
        if (ch == EOF) {
            break;
        }

        eon_str_add_char(str, (char) ch, has_err);

        if (*has_err) {
            EON_REF_DEC(str);
            return NULL;
        }
        if (ch == EON_END_OF_LINE) {
            break;
        }
    }

    return str;
}

static struct eon_str* token_read_whitespace(
        struct eon_input* input, bool* has_err) {

    struct eon_str* str = eon_str_new(has_err);
    if (*has_err) {
        return NULL;
    }

    while (true) {
        int ch = input->read(input, true, has_err);

        if (*has_err) {
            EON_REF_DEC(str);
            return NULL;
        }
        if ((ch != EON_SPACE) && (ch != EON_END_OF_LINE)) {
            break;
        }

        input->read(input, false, has_err); // Discard.
        eon_str_add_char(str, (char) ch, has_err);

        if (*has_err) {
            EON_REF_DEC(str);
            return NULL;
        }
    }

    return str;
}

struct eon_token* eon_token_parse(struct eon_input* input, bool* has_err) {
    int ch = input->read(input, true, has_err);

    if (*has_err || ch == EOF) {
        return NULL;
    }

    struct eon_str* str;
    enum eon_token_type type;
    size_t line = input->line;
    size_t col = input->col;

    if (ch == EON_COMMENT_QUOTE) {
        str = token_read_comment(input, has_err);
        type = EON_TOKEN_COMMENT;
    }
    else if ((ch == EON_SPACE) || (ch == EON_END_OF_LINE)) {
        str = token_read_whitespace(input, has_err);
        type = EON_TOKEN_WHITESPACE;
    }
    else {
        *has_err = true;
        EON_ERR_PRINTF("Unexpected token '%c' at %s:%zu:%zu",
            (char) ch, input->location, input->line, input->col);
        return NULL;
    }

    struct eon_token* token = token_new(type, str, input, line, col, has_err);
    EON_REF_DEC(str);
    return token;
}
