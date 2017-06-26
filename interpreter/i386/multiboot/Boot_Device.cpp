#include "../../core/Log.h"
#include "Boot_Device.h"

void e_Multiboot_Boot_Device::log() {
    e_Log_msg(e_Log_get(), E_LOG_INFO,
        "Boot device: drive={iuh}; partitions=[{iuh}, {iuh}, {iuh}]",
        this->drive_number,
        this->top_level_partition,
        this->sub_partition,
        this->sub_sub_partition);
}
