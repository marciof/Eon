#include <stdlib.h>
#include <unistd.h>
#include "input.h"

struct fd_buffer {
    int fd;
    char buf[BUFSIZ];
    size_t len;
    size_t pos;
    EON_REF_FIELDS;
};

static int fd_buffer_read(
        struct eon_input* input, bool is_peek, bool* has_err) {

    struct fd_buffer* fd_buffer = input->arg.ptr;

    if (fd_buffer->pos >= fd_buffer->len) {
        ssize_t len_bytes = read(
            fd_buffer->fd, fd_buffer->buf, BUFSIZ * sizeof(*fd_buffer->buf));

        if (len_bytes == -1) {
            *has_err = true;
            EON_ERR_ERRNO();
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

        if (ch == EON_END_OF_LINE) {
            ++input->line;
            input->col = 1;
        }
        else {
            ++input->col;
        }
    }

    return ch;
}

static void input_fd_buffer_free(void* ptr) {
    EON_REF_DEC((struct fd_buffer*) ((struct eon_input*) ptr)->arg.ptr);
    free(ptr);
}

struct eon_input* eon_input_from_fd(int fd, char* location, bool* has_err) {
    struct fd_buffer* fd_buffer = malloc(sizeof(*fd_buffer));

    if (fd_buffer == NULL) {
        *has_err = true;
        EON_ERR_ERRNO();
        return NULL;
    }

    struct eon_input* input = malloc(sizeof(*input));

    if (input == NULL) {
        *has_err = true;
        EON_ERR_ERRNO();
        free(fd_buffer);
        return NULL;
    }

    fd_buffer->fd = fd;
    fd_buffer->len = 0;
    fd_buffer->pos = 0;

    input->arg = eon_any_ptr(EON_REF_INIT(fd_buffer, free));
    input->location = location;
    input->line = 1;
    input->col = 1;
    input->read = fd_buffer_read;

    return EON_REF_INIT(input, input_fd_buffer_free);
}
