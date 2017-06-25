#include <stdlib.h>
#include "Input.h"
#include "Token.h"

int main() {
    bool has_err = false;
    struct Input* stdin_input = Input_from_stdin(&has_err);

    if (has_err) {
        return EXIT_FAILURE;
    }

    while (true) {
        struct Token* token = Token_read(stdin_input, &has_err);

        if (token == NULL) {
            break;
        }

        printf("[%.*s]", (int) token->str->len, token->str->val);
        REF_DEC(token);
    }

    REF_DEC(stdin_input);
    return has_err ? EXIT_FAILURE : EXIT_SUCCESS;
}
