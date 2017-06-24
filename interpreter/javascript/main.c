#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Any.h"
#include "Err.h"
#include "Str.h"

#define INPUT_READ_ERROR "Input read error"

struct Str* read_input_fd(union Any fd, struct Err* err) {
    char buffer[BUFSIZ];
    ssize_t len_bytes = read((int) fd.val, buffer, BUFSIZ * sizeof(*buffer));

    if (len_bytes == 0) {
        return NULL;
    }
    else if (len_bytes == -1) {
        ERR_ADD_ERRNO(err, errno);
        return ERR_ADD_CSTRING(err, INPUT_READ_ERROR);
    }

    struct Str* str = Str_from_chars(buffer, len_bytes / sizeof(*buffer), err);
    return ERR_HAS(err) ? ERR_ADD_CSTRING(err, INPUT_READ_ERROR) : str;
}

int main() {
    struct Err err = ERR_INIT_VAL;
    union Any stdin_fd = Any_val(STDIN_FILENO);

    while (true) {
        struct Str* buffer = read_input_fd(stdin_fd, &err);

        if (buffer == NULL) {
            break;
        }

        printf("%.*s", (int) buffer->len, buffer->val);
        REF_DEC(buffer);
    }

    if (ERR_HAS(&err)) {
        Err_print(&err, stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
