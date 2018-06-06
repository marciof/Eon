#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Input.h"

struct Fd_Buffer {
    int fd;
    size_t len;
    size_t pos;
    char buf[BUFSIZ];
};

static int peek_ch(struct k_Input* input, struct k_Err* err) {
    struct Fd_Buffer* fd_buffer = (struct Fd_Buffer*) input->val;

    if (fd_buffer->pos >= fd_buffer->len) {
        ssize_t len_bytes = read(
            fd_buffer->fd, fd_buffer->buf, BUFSIZ * sizeof(*fd_buffer->buf));

        if (len_bytes == -1) {
            K_ERR_SET_ERRNO(err, errno);
            return EOF;
        }
        else if (len_bytes == 0) {
            return EOF;
        }

        fd_buffer->len = len_bytes / sizeof(*fd_buffer->buf);
        fd_buffer->pos = 0;
    }

    return fd_buffer->buf[fd_buffer->pos];
}

static int read_ch(struct k_Input* input, struct k_Err* err) {
    int ch = peek_ch(input, err);

    if (k_Err_has(err)) {
        return EOF;
    }

    struct Fd_Buffer* fd_buffer = (struct Fd_Buffer*) input->val;
    ++fd_buffer->pos;

    if (ch == K_END_OF_LINE) {
        ++input->line;
        input->column = 1;
    }
    else {
        ++input->column;
    }

    return ch;
}

struct k_Input* k_Input_from_fd(int fd, char* location, struct k_Err* err) {
    struct k_Input* input = malloc(sizeof(*input) + sizeof(struct Fd_Buffer));

    if (input == NULL) {
        K_ERR_SET_ERRNO(err, errno);
        return NULL;
    }

    input->read_ch = read_ch;
    input->peek_ch = peek_ch;
    input->location = location;
    input->line = 1;
    input->column = 1;

    struct Fd_Buffer* fd_buffer = (struct Fd_Buffer*) input->val;
    fd_buffer->fd = fd;
    fd_buffer->len = 0;
    fd_buffer->pos = 0;

    return K_REF_INIT(input, free);
}
