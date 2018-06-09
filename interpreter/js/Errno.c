#include <string.h>
#include "../core/Log.h"
#include "Errno.h"

void k_Err_describe_errno(struct k_Err* err) {
    int num = (int) err->arg;
    k_Log_msg(k_Log_get(), err, K_LOG_ERROR,
        "{s} (errno 0x{ih})", strerror(num), num);
}
