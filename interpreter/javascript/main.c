#include <stdlib.h>
#include <unistd.h>
#include "eon/input.h"
#include "eon/token.h"

int main() {
    bool has_err = false;

    struct eon_input* stdin_input = eon_input_from_fd(
        STDIN_FILENO, "<stdin>", &has_err);

    if (has_err) {
        return EXIT_FAILURE;
    }

    while (true) {
        struct eon_token* token = eon_token_parse(stdin_input, &has_err);

        if (token == NULL) {
            break;
        }

        printf("%d[%.*s]", token->type, (int) token->str->len, token->str->val);
        EON_REF_DEC(token);
    }

    EON_REF_DEC(stdin_input);
    return has_err ? EXIT_FAILURE : EXIT_SUCCESS;
}
