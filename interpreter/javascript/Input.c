#include <stdlib.h>
#include <unistd.h>
#include "Input.h"

struct Fd_Buffer {
    int fd;
    char buf[BUFSIZ];
    size_t len;
    size_t pos;
    E_REF_FIELD;
};

static int e_Fd_Buffer_read(
        struct e_Input* input, bool is_peek, bool* has_err) {

    struct Fd_Buffer* fd_buffer = input->arg.ptr;

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

static void e_Input_Fd_Buffer_free(void* ptr) {
    E_REF_DEC((struct Fd_Buffer*) ((struct e_Input*) ptr)->arg.ptr);
    free(ptr);
}

struct e_Input* e_Input_from_fd(int fd, char* location, bool* has_err) {
    struct Fd_Buffer* fd_buffer = malloc(sizeof(*fd_buffer));

    if (fd_buffer == NULL) {
        *has_err = true;
        E_ERR_ERRNO();
        return NULL;
    }

    struct e_Input* input = malloc(sizeof(*input));

    if (input == NULL) {
        *has_err = true;
        E_ERR_ERRNO();
        free(fd_buffer);
        return NULL;
    }

    fd_buffer->fd = fd;
    fd_buffer->len = 0;
    fd_buffer->pos = 0;

    input->arg = e_Any_ptr(E_REF_INIT(fd_buffer, free));
    input->location = location;
    input->line = 1;
    input->column = 1;
    input->read = e_Fd_Buffer_read;

    return E_REF_INIT(input, e_Input_Fd_Buffer_free);
}
