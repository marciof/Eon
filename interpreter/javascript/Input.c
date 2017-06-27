#include <stdlib.h>
#include <unistd.h>
#include "Input.h"

struct Fd_Buffer {
    int fd;
    size_t len;
    size_t pos;
    char buf[BUFSIZ];
};

static int read_ch(struct e_Input* input, bool is_peek, bool* has_err) {
    struct Fd_Buffer* fd_buffer = (struct Fd_Buffer*) input->val;

    if (fd_buffer->pos >= fd_buffer->len) {
        ssize_t len_bytes = read(
            fd_buffer->fd, fd_buffer->buf, BUFSIZ * sizeof(*fd_buffer->buf));

        if (len_bytes == -1) {
            *has_err = true;
            E_ERR_ERRNO();
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

        if (ch == E_END_OF_LINE) {
            ++input->line;
            input->column = 1;
        }
        else {
            ++input->column;
        }
    }

    return ch;
}

struct e_Input* e_Input_from_fd(int fd, char* location, bool* has_err) {
    struct e_Input* input = malloc(sizeof(*input) + sizeof(struct Fd_Buffer));

    if (input == NULL) {
        *has_err = true;
        E_ERR_ERRNO();
        return NULL;
    }

    input->read_ch = read_ch;
    input->location = location;
    input->line = 1;
    input->column = 1;

    struct Fd_Buffer* fd_buffer = (struct Fd_Buffer*) input->val;
    fd_buffer->fd = fd;
    fd_buffer->len = 0;
    fd_buffer->pos = 0;

    return E_REF_INIT(input, free);
}
