#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../core/Log.h"
#include "Errno.h"
#include "Input.h"
#include "Token.h"

int main(void) {
    struct k_Err err = K_ERR_INIT;
    struct k_Input* stdin_input = k_Input_from_fd(
        STDIN_FILENO, "<stdin>", &err);

    if (k_Err_has(&err)) {
        return EXIT_FAILURE;
    }

    while (true) {
        struct k_Token* token = k_Token_parse(stdin_input, &err);

        if (token == NULL) {
            break;
        }

        printf("%d[%.*s]", token->type, (int) token->str->len, token->str->val);
        K_REF_DEC(token);
    }

    int exit_status;

    if (k_Err_has(&err)) {
        k_Log_error(k_Log_get(), &err);
        exit_status = EXIT_FAILURE;
    }
    else {
        exit_status = EXIT_SUCCESS;
    }

    K_REF_DEC(stdin_input);
    return exit_status;
}
