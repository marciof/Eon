#include <stdlib.h>
#include <unistd.h>
#include "Input.h"

struct Fd_Buffer {
    int fd;
    char buf[BUFSIZ];
    size_t len;
    size_t pos;
    REF_FIELDS;
};

static int Fd_Buffer_read(struct Input* input, bool is_peek, bool* has_err) {
    struct Fd_Buffer* fd_buffer = input->arg.ptr;

    if (fd_buffer->pos >= fd_buffer->len) {
        ssize_t len_bytes = read(
            fd_buffer->fd, fd_buffer->buf, BUFSIZ * sizeof(*fd_buffer->buf));

        if (len_bytes == -1) {
            *has_err = true;
            ERR_PRINT_ERRNO();
            return EOF;
        }
        else if (len_bytes == 0) {
            return EOF;
        }

        fd_buffer->len = len_bytes / sizeof(*fd_buffer->buf);
        fd_buffer->pos = 0;
    }

    int ch = fd_buffer->buf[fd_buffer->pos];

    if (!is_peek) {
        ++fd_buffer->pos;

        if (ch == END_OF_LINE) {
            ++input->line;
            input->col = 1;
        }
        else {
            ++input->col;
        }
    }

    return ch;
}

static void Input_Fd_Buffer_free(void* ptr) {
    REF_DEC((struct Fd_Buffer*) ((struct Input*) ptr)->arg.ptr);
    free(ptr);
}

struct Input* Input_from_stdin(bool* has_err) {
    struct Fd_Buffer* fd_buffer = malloc(sizeof(*fd_buffer));

    if (fd_buffer == NULL) {
        *has_err = true;
        ERR_PRINT_ERRNO();
        return NULL;
    }

    struct Input* input = malloc(sizeof(*input));

    if (input == NULL) {
        *has_err = true;
        ERR_PRINT_ERRNO();
        free(fd_buffer);
        return NULL;
    }

    fd_buffer->fd = STDIN_FILENO;
    fd_buffer->len = 0;
    fd_buffer->pos = 0;

    input->arg = Any_ptr(REF_INIT(fd_buffer, free));
    input->location = "<stdin>";
    input->line = 1;
    input->col = 1;
    input->read = Fd_Buffer_read;

    return REF_INIT(input, Input_Fd_Buffer_free);
}
