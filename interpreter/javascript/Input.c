#include <stdlib.h>
#include <unistd.h>
#include "Input.h"

static struct Str* read_stdin(union Any fd, bool* has_err) {
    char buffer[BUFSIZ];
    ssize_t len_bytes = read((int) fd.val, buffer, BUFSIZ * sizeof(*buffer));

    if (len_bytes == 0) {
        return NULL;
    }
    else if (len_bytes == -1) {
        *has_err = true;
        ERR_PRINT_ERRNO();
        return NULL;
    }

    return Str_from_chars(buffer, len_bytes / sizeof(*buffer), has_err);
}

struct Input* Input_from_stdin(bool* has_err) {
    struct Input* input = malloc(sizeof(*input));

    if (input == NULL) {
        *has_err = true;
        ERR_PRINT_ERRNO();
        return NULL;
    }

    input->arg = Any_val(STDIN_FILENO);
    input->location = "<stdin>";
    input->read = read_stdin;
    return REF_INIT(input, free);
}
