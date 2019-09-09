#include <string.h>
#include "../core/Log.h"
#include "Errno.h"

void k_Err_describe_errno(struct k_Err* err, k_Err_log log, intptr_t logger) {
    int num = (int) err->arg;
    log(logger, "{s} (errno 0x{ih})", strerror(num), num);
}
